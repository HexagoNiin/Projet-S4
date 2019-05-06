#include "../headers/utils_virtual_disk.h"

int init_disk_raid5(const char *repertoryName, int raid) {
	/// \brief Initialise la variable globale r5Disk
    /// \param[in] repertoryName : le repertoire ou se situe les disks
    /// \param[in] raid : type de RAID
    /// \return 0 si tout s'est bien passé, un entier positif sinon

	/* ouverture repertoire "repertoryName" */
    DIR *rep;
	if(!(rep = opendir(repertoryName))) {
		fprintf(stderr, "Erreur lors de l'ouverture du repertoire.\n");
		return 1;
	}

	/* compte nombre de disks */
	int nbFiles = 0;
	struct dirent *disk;
    while((disk = readdir(rep))) {
		if(strcmp(disk->d_name, ".") && strcmp(disk->d_name, ".."))
			nbFiles++;
    }

	/* ouverture des disks */
	rewinddir(rep);
	FILE **storage = malloc(sizeof(FILE *) * nbFiles);
	int i = 0;
    char *chemin = NULL;
	while((disk = readdir(rep))) {
		if(strcmp(disk->d_name, ".") && strcmp(disk->d_name, "..")) {
			chemin = malloc(sizeof(char) * (strlen(repertoryName) + strlen(disk->d_name) + 2));
			sprintf(chemin, "%s/%s", repertoryName, disk->d_name);
			if(!(storage[i] = fopen(chemin, "r+"))) {
				fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", disk->d_name);
                free(chemin);
				return 2;
			}
			i++;
            free(chemin);
		}
    }
    closedir(rep);

    r5Disk.ndisk = nbFiles;
    r5Disk.storage = storage;
    r5Disk.raidmode = raid;

    /* detection de la table d'inode */
    int exit_read = read_super_block();
    if(exit_read || check_super_block()) {
        printf("Systeme inexistant : mise en place du systeme RAID\n");

        /* initialisation r5Disk */
        r5Disk.super_block.raid_type = raid;
        r5Disk.number_of_files = 0;
        r5Disk.super_block.nb_blocks_used = INODE_SIZE * INODE_TABLE_SIZE + SUPER_BLOCK_SIZE;
        r5Disk.super_block.first_free_byte = ((INODE_SIZE * INODE_TABLE_SIZE + SUPER_BLOCK_SIZE) / nbFiles) * BLOCK_SIZE;
		log1("FIRST FREE BYTE : %d", r5Disk.super_block.first_free_byte)
        int u;
        for(u=0;u<INODE_TABLE_SIZE;u++)
            r5Disk.inodes[u].first_byte = 0;
        write_super_block();
		write_inodes_table((SUPER_BLOCK_SIZE / r5Disk.ndisk) * BLOCK_SIZE);
    } else {
        printf("Detection du systeme RAID\n");
        int u;
        if(read_inodes_table(SUPER_BLOCK_SIZE / r5Disk.ndisk * BLOCK_SIZE))
            return EXIT_FAILURE;
        for(u=0;r5Disk.inodes[u].first_byte;u++);
        r5Disk.number_of_files = u;
    }

	return EXIT_SUCCESS;
}

uchar *xor_uchar(uchar *a, uchar *b, int size) {
	uchar *buffer = malloc(size * sizeof(uchar));
	for(int i = 0; i < size; i++)
		buffer[i] = a[i] ^ b[i];
	return buffer;
}

void close_system() {
    /// \brief Ferme le système RAID
	int u;
	for(u=0;u<r5Disk.ndisk;u++)
		fclose(r5Disk.storage[u]);
}

int repair_disk(int num) {
    /// \brief Regénère un disque à partir des autres disques
    /// \param[in] num : le numéro du disque à générer
    /// \return 0
	int num_ref = (!num) ? (1) : (0);
	fseek(r5Disk.storage[num_ref], 0, SEEK_END);
	size_t size = ftell(r5Disk.storage[num_ref]);
	fseek(r5Disk.storage[num_ref], 0, SEEK_SET);
	uchar *buffer_lecture = malloc(size * sizeof(uchar));
	uchar *buffer_ecriture = malloc(size * sizeof(uchar));
	fread(buffer_ecriture, sizeof(uchar), size, r5Disk.storage[num_ref]);
	for(int i = num_ref + 1; i < r5Disk.ndisk; i++) {
		if(i != num) {
			fseek(r5Disk.storage[i], 0, SEEK_SET);
			fread(buffer_lecture, sizeof(uchar), size, r5Disk.storage[i]);
			buffer_ecriture = xor_uchar(buffer_lecture, buffer_ecriture, size);
		}
	}
	fseek(r5Disk.storage[num], 0, SEEK_SET);
	fwrite(buffer_ecriture, sizeof(uchar), size, r5Disk.storage[num]);
	return EXIT_SUCCESS;
}

int check_super_block() {
    /// \brief Vérifie que les données du super block sont correctes
    /// \return 1 si l'opération s'est mal passée, 0 sinon
    log1("[CHECK_SUPER_BLOCK] raid_type : %d first_free_byte : %d blocks : %d", r5Disk.super_block.raid_type, r5Disk.super_block.first_free_byte, r5Disk.super_block.nb_blocks_used);
    if(r5Disk.super_block.raid_type < 1 || r5Disk.super_block.raid_type > 7)
        return EXIT_FAILURE;
    if(r5Disk.super_block.first_free_byte < 0 || r5Disk.super_block.nb_blocks_used <0)
        return EXIT_FAILURE;
    return EXIT_SUCCESS;
}

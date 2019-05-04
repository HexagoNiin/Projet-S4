#include "../headers/utils_virtual_disk.h"

int init_disk_raid5(const char* repertoryName) {
	/// \brief Initialise la variable globale r5Disk
    /// \param[in] repertoryName : le repertoire ou se situe les disks

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
	while((disk = readdir(rep))) {
		if(strcmp(disk->d_name, ".") && strcmp(disk->d_name, "..")) {
			char *chemin = malloc(sizeof(char) * (strlen(repertoryName) + strlen(disk->d_name) + 2));
			sprintf(chemin, "%s/%s", repertoryName, disk->d_name);
			/* ouverture des disks du repertoire */
			if(!(storage[i] = fopen(chemin, "r+"))) {
				fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", disk->d_name);
				return 2;
			}
			i++;
            free(chemin);
		}
    }
    closedir(rep);

	/* initialisation r5Disk */
    r5Disk.ndisk = nbFiles;
    r5Disk.storage = storage;
    r5Disk.super_block.raid_type = CINQ;
    r5Disk.raidmode = CINQ;
    if(read_inodes_table((SUPER_BLOCK_SIZE / r5Disk.ndisk) * BLOCK_SIZE)) {
        printf("Systeme inexistant : mise en place du systeme RAID\n");
        r5Disk.number_of_files = 0;
        r5Disk.super_block.nb_blocks_used = INODE_SIZE * INODE_TABLE_SIZE + SUPER_BLOCK_SIZE;
        r5Disk.super_block.first_free_byte = ((INODE_SIZE * INODE_TABLE_SIZE + SUPER_BLOCK_SIZE) / nbFiles) * BLOCK_SIZE;
        int u;
        for(u=0;u<INODE_TABLE_SIZE;u++) {
            r5Disk.inodes[u].first_byte = 0;
        }
        write_super_block();
        write_inodes_table(r5Disk.super_block.first_free_byte);
    } else {
        printf("Detection du systeme RAID\n");
        int u;
        for(u=0;r5Disk.inodes[u].first_byte;u++);
        r5Disk.number_of_files = u;
        if(read_super_block()) {
            fprintf(stderr, "Erreur lors de la lecture du super block.\n");
            return 3;
        }
    }

	return EXIT_SUCCESS;
}

uchar *xor_uchar(uchar *a, uchar *b, int size) {
	uchar *buffer = malloc(size * sizeof(uchar));
	for(int i = 0; i < size; i++) {
		buffer[i] = a[i] ^ b[i];
		//printf("%x xor %x\n", a[i], b[i]);
	}
	return buffer;
}

void close_system() {
	int u;
	for(u=0;u<r5Disk.ndisk;u++)
		fclose(r5Disk.storage[u]);
}

int repair_disk(int num) {
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

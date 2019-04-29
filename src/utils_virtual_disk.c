#include "../headers/utils_virtual_disk.h"

int init_disk_raid5(const char* repertoryName) {
	/// \brief Initialise la variable globale r5Disk
    /// \param[in] repertoryName : le repertoire ou se situe les disks

	/* ouverture repertoire "repertoryName" */
    DIR *rep;
	if(!(rep = opendir(repertoryName))) {
		fprintf(stderr, "Erreur lors de l'ouverture du repertoire.\n");
		exit(1);
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
			char* chemin = malloc(sizeof(char*));
			sprintf(chemin, "%s/%s", repertoryName, disk->d_name);
			/* ouverture des disks du repertoire */
			if(!(storage[i] = fopen(chemin, "r+"))) {
				fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", disk->d_name);
				exit(2);
			}
			i++;
		}
    }
    closedir(rep);

	/* initialisation r5Disk */
	r5Disk.number_of_files = 0;
	r5Disk.super_block.raid_type = CINQ;
	r5Disk.super_block.nb_blocks_used = 0;
	r5Disk.super_block.first_free_byte = (SUPER_BLOCK_SIZE / nbFiles) * BLOCK_SIZE + (write_inodes_table((SUPER_BLOCK_SIZE / r5Disk.ndisk) * BLOCK_SIZE) * BLOCK_SIZE);
	r5Disk.ndisk = nbFiles;
	r5Disk.raidmode = CINQ;
	r5Disk.storage = storage;

	return 0;
}

uchar *xor_uchar(uchar *a, uchar *b, int size) {
	uchar *buffer = malloc(size * sizeof(uchar));
	for(int i = 0; i < size; i++) {
		buffer[i] = a[i] ^ b[i];
		printf("%x xor %x\n", a[i], b[i]);
	}
	return buffer;
}

int repair_disk(int num) {
	int num_ref = (num == 0) ? (1) : (0);
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
	return 0;
}

/*int init_disk_raid5(const char* nom_rep, virtual_disk_t* r5Disk) {
    /// \brief Initialise la variable globale virtual_disk_t r5Disk à partir de nom_rep
    /// \param[in] nom_rep : Nom du répertoire contenant les disques virtuels formatés
    /// \return Un entier indiquant si l'opération s'est bien passée
    DIR *rep = opendir(nom_rep);
    struct dirent *disque;
    r5Disk->raidmode = CINQ;
    r5Disk->number_of_files = 0; //Quelle est la différence entre cet attribut et l'attribut ndisk ? En attendant je le mets à 0.
    //Non initialisés : inodes (Il est demandé de ne pas le faire pour l'instant), super_block (Je sais pas encore ce que c'est sensé être),

    if(rep == NULL) {
        fprintf(stderr, "Une erreur est survenue lors de l'accès au répertoire %s.\n", nom_rep);
        return 1;
    }

    r5Disk->ndisk = 0;
    r5Disk->storage = malloc(sizeof(FILE*));
    while((disque = readdir(rep)) != NULL) {
        struct stat sDisque;
        if(stat(disque->d_name, &sDisque) == -1) {
            fprintf(stderr, "Une erreur est survenue lors de la lecture du disque %s.\n", disque->d_name);
            return 2;
        }
        if(S_ISREG(sDisque.st_mode)) {
            fprintf(stderr, "L'élément %s est étranger au système. L'élément devrait être supprimé ou le système reformaté.\n", disque->d_name);
            return 3;
        }
        r5Disk->ndisk++; //J'imagine que c'est le nombre de disque ? Ce n'est ni commenté, ni documenté.
        r5Disk->storage = realloc(r5Disk->storage, r5Disk->ndisk * sizeof(FILE*));
        r5Disk->storage[r5Disk->ndisk-1] = fopen(disque->d_name, "r");
    }
    return 0;
}*/

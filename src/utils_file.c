#include "../headers/utils_file.h"

int write_file(const char *filename, file_t file) {
    /// \brief Ecrit un fichier sur le système
    /// \param[in] filename : filename du fichier à écrire
    /// \param[in] file : fichier à écrire
	log2("[WRITE_FILE] Écriture sur le système de %s", filename);
    int i, u;
    for(i=0;i<INODE_TABLE_SIZE && (u = strcmp(filename, r5Disk.inodes[i].filename));i++);
    if(!u) {
        if(r5Disk.inodes[i-1].size <= file.size) {
            /* mise a jour du RAID */
            int nstripe;
            nstripe = write_chunk(file.data, file.size, r5Disk.inodes[i-1].first_byte);
            /* mise a jour de l'inode */
            r5Disk.inodes[i-1].size = file.size;
            strcpy(r5Disk.inodes[i-1].filename, filename);
            r5Disk.inodes[i-1].nblock = nstripe * r5Disk.ndisk;
            return 0;
        } else {
            /* supprimer inode */
            delete_inode(i-1);
        }
    }
    /* creation inode et mise a jour de la table d'inodes */
    inode_t inode = init_inode(filename, file.size, r5Disk.super_block.first_free_byte);
    /* ecriture fichier */
    int size = write_chunk(file.data, file.size, r5Disk.super_block.first_free_byte);
    if(size == -1) {
        fprintf(stderr, "Erreur lors de l'ecriture du fichier.\n");
		return 1;
    }
    inode.nblock = size * r5Disk.ndisk;
    update_inodes_table(inode);
    return 0;
}

int read_file(const char* filename, file_t *file){
	/** 	\brief lit un fichier du système
	\param[in] filename : filename du fichier à lire
	\param[in] fichier : fichier de lecture
	*/
	log2("[READ_FILE] Lecture sur le système de %s", filename);
	//char c;
	  int i = 0;
	  int file_exist = 0;

	  while(i < INODE_TABLE_SIZE && !file_exist){
	    if (strcmp(filename, r5Disk.inodes[i].filename) == 0){
	      file_exist = 1;
	    }
	    else{
	      i++;
	    }
	  }

	if(!file_exist){
		return 1;
	}

	file->size = r5Disk.inodes[i].size;

	read_chunk(file->data, file->size, r5Disk.inodes[i].first_byte);

	return 0;
}

int load_file_from_host(const char *filename) {
	log2("[LOAD_FILE_FROM_HOST] Chargement vers le disque virtuel de %s", filename);
	FILE* f = fopen(filename, "r");
	if(f == NULL) return 2;
	file_t file;
	fseek(f, 0, SEEK_END);
	file.size = ftell(f);
	fseek(f, 0, SEEK_SET);
	for(int i = 0; i < file.size && i < MAX_FILE_SIZE; i++) file.data[i] = fgetc(f);
	fclose(f);
	return write_file(filename, file);
}

int store_file_to_host(const char *filename) {
	log2("[STORE_FILE_TO_HOST] Importation depuis le disque virtuel de %s", filename);
	file_t file;
	if(read_file(filename, &file)) return 1;
	FILE* f = fopen(filename, "w");
	if(f == NULL) return 2;
	log2("[STORE_FILE_TO_HOST] Données lues (%d caractères) : %s", file.size, file.data)
	if(fwrite(file.data, sizeof(uchar), file.size, f) != file.size) return 3;
	fclose(f);
	return 0;
}

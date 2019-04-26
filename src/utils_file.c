#include "../headers/utils_file.h"

void write_file(const char *filename, file_t file) {
    /// \brief Ecrit un fichier sur le système
    /// \param[in] filename : nom du fichier à écrire
    /// \param[in] file : fichier à écrire
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
            r5Disk.inodes[i-1].nblock = (file.size + BLOCK_SIZE - 1) / BLOCK_SIZE;
            return ;
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
        exit(1);
        fprintf(stderr, "Erreur lors de l'ecriture du fichier.\n");
    }
    inode.nblock = size * r5Disk.disk;
    update_inodes_table(inode);
    return ;
}

int read_file(const char *namefile, file_t *file) {
	return 0;
}

void load_file_from_host(const char *filename) {
	FILE* f = fopen(filename, "r");
	file_t file;
	file.size = fseek(f, 0, SEEK_END)+1;
	fseek(f, 0, SEEK_SET);
	for(int i = 0; i < file.size && i < MAX_FILE_SIZE; i++) file.data[i] = fgetc(f);
	fclose(f);
	write_file(filename, file);
}

void store_file_to_host(const char *filename) {
	file_t file;
	read_file(filename, &file);
	FILE* f = fopen(filename, "w");
	fwrite(file.data, sizeof(uchar), file.size, f);
	fclose(f);
}

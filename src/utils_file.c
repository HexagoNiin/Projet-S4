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

void store_file_from_host() {

}

void load_file_from_host() {

}

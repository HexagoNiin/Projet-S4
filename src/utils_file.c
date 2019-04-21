#include "../headers/utils_file.h"

void write_file(char *filename, file_t file) {
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
            delete_inode(r5Disk.inodes, i-1);
        }
    }
    /* creation inode et mise a jour de la table d'inodes*/
    init_inode(filename, file.size, r5Disk.super_block.first_free_byte);
    /* ecriture fichier */
    write_chunk(file.data, file.size, r5Disk.super_block.first_free_byte);
    return ;
}

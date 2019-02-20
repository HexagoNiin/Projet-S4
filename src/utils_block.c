#include "../headers/utils_block.h"

int write_block(block_t block, int pos, int disk_id) {
    /// \brief Ecrit un block sur un disque à une position donnée
    /// \param[in] block : Block à écrire sur le disk
    /// \param[in] pos : Position où écrire le block
    /// \param[in] disk_id : Disk sur lequel écrire le block
    /// \return Un entier indiquant si l'opération s'est bien passée
    lseek(disk_id, pos, SEEK_SET);
    if(write(disk_id, &block, sizeof(block_t)) != sizeof(block_t)) {
        fprintf(stderr, "Une erreur est survenue lors de l'ecriture du block.\n");
        return EXIT_FAILURE; //1
    }
    return EXIT_SUCCESS; //0
}

int block_repair(int pos, int disks[], int id_disk, int nbr_disks) {
    /// \brief Répare un block erroné
    /// \param[in] pos : Position du block eronné
    /// \param[in] disks : Tableau des disks utilisés par le RAID
    /// \param[in] disk_id : Index du disk avec le block eronné
    /// \return Un entier indiquant si l'opération s'est bien passée
    int i, j;
    block_t block_repare;
    block_t * block;
    for(i=0;i<nbr_disks;i++) {//nbr_disks à transformer en DEFINE ?
        if(!read_block(block, pos, disks[i])) {
            fprintf(stderr, "Une erreur est survenue, il y a au moins deux blocks qui ont ete corrompus.\n");
            return 1;
        }
        for(j=0;j<BLOCK_SIZE;j++)
            block_repare.data[j] ^= block->data[j];
    }
    if(!write_block(block_repare, pos, disks[id_disk])) {
        return 0;
    } return 2;
}

#include "../headers/utils_block.h"

block_t create_block() { //Utilisé dans utils_stripe.c
	/// \brief Crée un block vide
    /// \return Un block initialisé à 0
	block_t block; //Block renvoyé
    for(int i = 0; i < BLOCK_SIZE; i++) { //Initialisation du block de parité
        block.data[i] = 0;
    }
	return block;
}

int compute_nblock(int nb_octets) {
    /// \brief Calcule le nombre de blocks nécessaires pour stocker nb_octets octets
    /// \param[in] nb_octets : Nombre d'octets à stocker
    /// \return Nombre de blocks nécessaires
	return nb_octets / 4 + (nb_octets % 4 != 0);
}

int write_block(block_t block, int pos, FILE * disk_id) {
    /// \brief Ecrit un block sur un disque à une position donnée
    /// \param[in] block : Block à écrire sur le disk
    /// \param[in] pos : Position où écrire le block
    /// \param[in] disk_id : Disk sur lequel écrire le block
    /// \return Un entier indiquant si l'opération s'est bien passée
    fseek(disk_id, pos, SEEK_SET);
    if(fwrite(&block, sizeof(block_t), 1, disk_id) != 1) {
        fprintf(stderr, "Une erreur est survenue lors de l'ecriture du block.\n");
        return EXIT_FAILURE; //1
    }
    return EXIT_SUCCESS; //0
}

void print_block(block_t block) {
    int i;
    for(i=0;i<BLOCK_SIZE;i++)
    printf("%c ", block.data[i]);
    printf("\n");
}

int block_repair(int pos, FILE  *disks[], int id_disk, int nbr_disks) {
    /// \brief Répare un block erroné
    /// \param[in] pos : Position du block eronné
    /// \param[in, out] disks : Tableau des disks utilisés par le RAID
    /// \param[in] disk_id : Index du disk avec le block eronné
    /// \param[in] nbr_disks : Nombre de disks utilisés par le RAID
    /// \return Un entier indiquant si l'opération s'est bien passée
    int i, j;
    block_t block_repare;
    block_t * block;
    for(i=0;i<nbr_disks;i++) {//nbr_disks à transformer en DEFINE ?
        if(i != id_disk) {
            if(!read_block(block, pos, disks[i])) {
                fprintf(stderr, "Une erreur est survenue, il y a au moins deux blocks qui ont ete corrompus.\n");
                return 1;
            }
            for(j=0;j<BLOCK_SIZE;j++)
                block_repare.data[j] ^= block->data[j];
        }
    }
    if(!write_block(block_repare, pos, disks[id_disk])) {
        return 0;
    } return 2;
}

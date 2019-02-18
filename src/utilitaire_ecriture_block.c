#include "../headers/utilitaire_ecriture_block.h"

int write_block(block_t block, int pos, int disk_id) {
    /// \brief Ecrit un block sur un disque à une position donnée
    /// \param[in] block : Block à écrire sur le disk
    /// \param[in] pos : Position où écrire le block
    /// \param[in] disk_id : Disk sur lequel écrire le block
    /// \return Un entier indiquant si l'opération s'est bien passée
    lseek(disk_id, pos, SEEK_SET);
    if(write(disk_id, &block, sizeof(block_t)) != sizeof(block_t)) {
        fprintf(stderr, "Une erreur est survenue lors de l'ecriture du block.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

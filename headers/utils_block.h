/// \file utils_block.h
/// \brief Utilitaires permettant de manipuler la structure block_s
/// \author Ugo EB-LEVADOUX
/// \author Axel GAUTHIER
/// \author Cédric MARTIN
/// \date 2019
#ifndef _UTILS_BLOCK
#define _UTILS_BLOCK

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "raid_defines.h"

int compute_nblock(int nb_octets);
int write_block(block_t block, int pos, FILE * disk_id);
//int block_repair(int pos, int disks[], int id_disk, int nbr_disks);

#endif

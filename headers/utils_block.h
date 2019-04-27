/// \file utils_block.h
/// \brief Utilitaires permettant de manipuler la structure block_s
/// \author Ugo EB-LEVADOUX
/// \author Axel GAUTHIER
/// \author Cédric MARTIN
/// \date 2019
#ifndef _UTILS_BLOCK
#define _UTILS_BLOCK

#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "raid_defines.h"
#include "utils_virtual_disk.h"

#define BLOCKS_ARE_STRINGS 1

block_t create_block();
block_t tab_to_block(uchar *tab);
int read_block (block_t *block, uint pos, FILE *disk);
int compute_nblock(int nb_octets);
int write_block(block_t block, int pos, FILE * disk_id);
void print_block(block_t block);
int block_repair(int pos, int id_disk);
int read_block (block_t *block, uint pos /*position d'un block*/ , FILE *disk);
char* itoh(int x); //Pas nécessairement dans le header
void display_block(block_t block);
int display_pos(uint pos, FILE* disk);

#endif

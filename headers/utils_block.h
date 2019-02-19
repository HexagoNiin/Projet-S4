#ifndef _UTILITAIRE_ECRITURE_BLOCK
#define _UTILITAIRE_ECRITURE_BLOCK

#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include "raid_defines.h"

int write_block(block_t block, int pos, int disk_id);
int block_repair(int pos, block_t [] blocks);

#endif

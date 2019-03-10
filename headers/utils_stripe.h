#ifndef _UTILS_STRIPE
#define _UTILS_STRIPE

#include "utils_block.h"

int write_stripes(stripe_t stripe, int pos, FILE ** disks);
int write_chunk(uchar * buffer, int nChars, int startbyte, FILE ** disks);
int compute_parity_index(int i);
int compute_nstripe(int i);
block_t compute_parity(block_t *blocks, int nb_disks);
void print_stripe(stripe_t stripe);

#endif

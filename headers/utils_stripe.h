/// \file utils_stripe.h
/// \brief Utilitaires permettant de manipuler la structure stripe_s
/// \author Ugo EB-LEVADOUX
/// \author Axel GAUTHIER
/// \author Cédric MARTIN
/// \date 2019
#ifndef _UTILS_STRIPE
#define _UTILS_STRIPE

#include "utils_block.h"

int read_chunk(uchar *buffer, int nStripe, int startbyte, FILE **disk);
int read_strip(stripe_t *stripe, uint pos, FILE ** disk);
int write_stripes(stripe_t stripe, int pos);
int write_chunk(uchar * buffer, int nChars, int startbyte);
block_t *generateStripe(uchar *buffer, int nChars, int *posCurrent);
int compute_parity_index(int i);
int compute_nstripe(int i);
block_t compute_parity(block_t *blocks, int nb_block);
void print_stripe(stripe_t stripe);

#endif

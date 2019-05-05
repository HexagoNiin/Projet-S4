/// \file utils_stripe.h
/// \brief Utilitaires permettant de manipuler la structure stripe_s
/// \author Ugo EB-LEVADOUX
/// \author Axel GAUTHIER
/// \author Cédric MARTIN
/// \date 2019
#ifndef _UTILS_STRIPE
#define _UTILS_STRIPE

#include "utils_block.h"

int read_chunk(uchar *buffer, int nChars, int startbyte);
int read_chunk_raid5(uchar * buffer, int nChars, int startbyte);
int read_chunk_raid0(uchar *buffer, int nChars, int startbyte);
int read_chunk_raid1(uchar * buffer, int nChars, int startbyte);
int read_chunk_raid50(uchar * buffer, int nChars, int startbyte);
int read_chunk_raid1(uchar *buffer, int nChars, int startbyte);
int read_chunk_raid5(uchar *buffer, int nChars, int startbyte);
int read_stripe(stripe_t *stripe, uint pos);
int write_stripe(stripe_t stripe, int pos);
int write_chunk(uchar * buffer, int nChars, int startbyte);
int write_chunk_raid0(uchar * buffer, int nChars, int startbyte);
int write_chunk_raid1(uchar * buffer, int nChars, int startbyte);
int write_chunk_raid5(uchar * buffer, int nChars, int startbyte);
int write_chunk_raid50(uchar * buffer, int nChars, int startbyte);
int compute_parity_index(int i, int ndisk);
int compute_nstripe(int i);
block_t compute_parity(block_t *blocks, int nb_disks);
void print_stripe(stripe_t stripe);

#endif

#ifndef _UTILS_STRIPE
#define _UTILS_STRIPE

#include "utils_block.h"

int write_stripes(stripe_t stripe, int pos, FILE ** disks);
int write_chunk(uchar * buffer, int nChars, int startbyte, FILE ** disks);

#endif

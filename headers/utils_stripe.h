#ifndef _UTILS_STRIPE
#define _UTILS_STRIPE

#include "utils_block.h"

int write_stripes(stripe_t stripe, int pos, int * disks);
int write_chunk(char * buffer, int nChars, int startbyte, int * disks);

#endif

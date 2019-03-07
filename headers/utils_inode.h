#ifndef _UTILS_INODE
#define _UTILS_INODE

#include "utils_stripe.h"
#include "string.h"

int write_inodes_table(inode_t inode, int pos, FILE **files);

#endif

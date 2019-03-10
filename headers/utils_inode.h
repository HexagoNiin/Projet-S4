#ifndef _UTILS_INODE
#define _UTILS_INODE

#include "utils_stripe.h"
#include "string.h"

int write_inodes_table(inode_table_t inode, FILE **files);
int get_unused_inode(inode_table_t inodes);
char *indtostr(inode_t inode);

#endif

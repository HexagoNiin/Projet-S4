/// \file utils_inode.h
/// \brief Utilitaires permettant de manipuler la structure inode_s
/// \author Ugo EB-LEVADOUX
/// \author Axel GAUTHIER
/// \author Cédric MARTIN
/// \date 2019
#ifndef _UTILS_INODE
#define _UTILS_INODE

#include "utils_stripe.h"
#include "string.h"

int delete_inode(inode_table_t *inodeTable, int pos);
int write_inodes_table(inode_table_t inode, FILE **files);
int get_unused_inode(inode_table_t inodes);
int read_inodes_table(inode_table_t able, FILE **raid);
uchar *indtostr(inode_t inode);

#endif

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

void delete_inode(int pos);
int write_inodes_table(int startbyte);
int get_unused_inode();
<<<<<<< HEAD
int read_inodes_table();
uchar *indtostr(inode_t inode);
uchar *sbtostr();
int write_super_block(int *startbyte);
inode_t init_inode(char *filename, uint size, uint position);
int update_inodes_table(inode_t inode);
void update_first_free_byte(int new_byte);
=======
int read_inodes_table(inode_table_t table, FILE **raid);
uchar *indtostr(inode_t inode);
uchar *sbtostr();
int write_super_block(int *startbyte);
inode_t init_inode(char *filename, uint size, uint pos);
int update_inodes_table(inode_t inode, int new_byte);
>>>>>>> c2d324ec218c5d677fcfe4136bc5a332c2d6e826
#endif

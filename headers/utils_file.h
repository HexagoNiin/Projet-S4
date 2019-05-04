/// \file utils_inode.h
/// \brief Utilitaires permettant de manipuler la structure file_s
/// \author Ugo EB-LEVADOUX
/// \author Axel GAUTHIER
/// \author Cédric MARTIN
/// \date 2019
#ifndef _UTILS_FILE
#define _UTILS_FILE
#include "../headers/utils_inode.h"

int write_file(const char *filename, file_t file);
int read_file(const char *filename, file_t *file);
int load_file_from_host(const char *filename);
int store_file_to_host(const char *filename);

#endif

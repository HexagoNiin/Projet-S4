/// \file utils_inode.h
/// \brief Utilitaires permettant de manipuler la structure file_s
/// \author Ugo EB-LEVADOUX
/// \author Axel GAUTHIER
/// \author Cédric MARTIN
/// \date 2019
#ifndef _UTILS_FILE
#define _UTILS_FILE
#include <string.h>
#include "../headers/raid_defines.h"
#include "../headers/utils_inode.h"
#include "../headers/utils_stripe.h"

void write_file(char *filename, file_t file);
void write_file(const char *filename, file_t file);
void load_file_from_host(const char *filename);
void store_file_to_host(const char *filename);

#endif

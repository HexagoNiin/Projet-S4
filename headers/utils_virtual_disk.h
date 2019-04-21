/// \file utils_virtual_disk.h
/// \brief Utilitaires permettant de manipuler la structure virtual_disk_s
/// \author Ugo EB-LEVADOUX
/// \author Axel GAUTHIER
/// \author Cédric MARTIN
/// \date 2019
#ifndef _UTILS_VIRTUAL_DISK
#define _UTILS_VIRTUAL_DISK

#include <unistd.h>
#include <stdlib.h>
#include "raid_defines.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int init_disk_raid5(const char* repertoryName);

#endif

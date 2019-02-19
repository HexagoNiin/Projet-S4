#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../headers/utilitaire_ecriture_block.h"
#include "../headers/raid_defines.h"

int main(void) {

    int f = open("truc.txt", O_WRONLY);
    block_t block;
    block.data[0] = 'c';
    block.data[1] = 'e';
    block.data[2] = 'f';
    block.data[3] = 'o';
    write_block(block, -7, f);
    close(f);
    return 0;
}

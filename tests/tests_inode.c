#include "../headers/utils_inode.h"
#include <stdio.h>
int main(void) {
    FILE **file = malloc(sizeof(FILE*)*4);

    file[0] = fopen("systeme/d0", "w");
    file[1] = fopen("systeme/d1", "w");
    file[2] = fopen("systeme/d2", "w");
    file[3] = fopen("systeme/d3", "w");
    if(file[0] == NULL || file[1] == NULL || file[2] == NULL || file[3] == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture des fichiers\n");
        exit(1);
    }
    inode_t inode;
    inode.filename[0] = 'l';
    inode.filename[1] = 'o';
    inode.filename[2] = 'l';
    inode.filename[3] = '\0';
    inode.size = -1;
    inode.nblock = -2;
    inode.first_byte = -3;
    write_inodes_table(inode, 0, file);
    fclose(file[0]);
    fclose(file[1]);
    fclose(file[2]);
    fclose(file[3]);
    free(file);
    return 0;
}
 /*gcc tests/tests_stripe.c src/utils_block.c src/utils_stripe.c -o slt*/

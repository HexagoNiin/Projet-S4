#include "../headers/utils_stripe.h"
#include <stdio.h>
int main(void) {
    uchar tab[8192];
    int i;
    FILE **file = malloc(sizeof(FILE*)*4);
    for(i=0;i<8192;i++){
        tab[i] = (char)(64 + (i%26));
    }

    file[0] = fopen("systeme/d0", "w");
    file[1] = fopen("systeme/d1", "w");
    file[2] = fopen("systeme/d2", "w");
    file[3] = fopen("systeme/d3", "w");
    if(file[0] == NULL || file[1] == NULL || file[2] == NULL || file[3] == NULL) {
        fprintf(stderr, "Erreur lors de l'ouverture des fichiers\n");
        exit(1);
    }
    write_chunk(tab, 1024, 0, file);
    fclose(file[0]);
    fclose(file[1]);
    fclose(file[2]);
    fclose(file[3]);
    free(file);
    return 0;
}
 /*gcc tests/tests_stripe.c src/utils_block.c src/utils_stripe.c -o slt*/

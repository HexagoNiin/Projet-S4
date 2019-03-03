#include "../headers/utils_stripe.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    char tab[1024];
    int i, file[4];
    for(i=0;i<1024;i++){
        tab[i] = (char)(64 + (i%26));
    }

    file[0] = open("systeme_test/d0", O_WRONLY);
    file[1] = open("systeme_test/d1", O_WRONLY);
    file[2] = open("systeme_test/d2", O_WRONLY);
    file[3] = open("systeme_test/d3", O_WRONLY);
    if(file[0] == -1 || file[1] == -1 || file[2] == -1 || file[3] == -1) {
        fprintf(stderr, "oups\n");
        exit(1);
    }
    write_chunk(tab, 1024, 0, file);
    return 0;
}
 /*gcc tests/tests_stripe.c src/utils_block.c src/utils_stripe.c -o slt*/

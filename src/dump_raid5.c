#include <stdio.h>
#include <stdlib.h>
#include "../headers/utils_stripe.h"
#include "../headers/utils_virtual_disk.h"

int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage : <%s> repertory size\n", argv[0]);
        return 1;
    }
    int N = atoi(argv[2]);
    if(N < 0) {
        fprintf(stderr, "La size doit etre positive.\n");
        return 2;
    }
    init_disk_raid5(argv[1]);
    stripe_t stripe;
    int u, i;
    for(u=0;u<N;u+=BLOCK_SIZE) {
        read_stripe(&stripe, u);
        for(i=0;i<BLOCK_SIZE;i++) {
            display_block(stripe.stripe[i]);
            printf(" ");
        }
        printf("Parite : %d\n\n", 3 - compute_parity_index(u / BLOCK_SIZE));
    }

    return 0;
}

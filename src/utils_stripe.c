#include "../headers/utils_stripe.h"

int write_stripes(stripe_t stripe, int pos, int * disks) {
    int i;
    for(i=0;i<stripe.nblocks;i++) {
            if(write_block(stripe.stripe[i], pos, disks[i])) {
                fprintf(stderr, "Erreur lors de l'ecriture de la bande.\n");
                return EXIT_FAILURE;
            }
    }
    return EXIT_SUCCESS;
}

int write_chunk(char * buffer, int nChars, int startbyte, int * disks) {
    int i, j, u;
    int nChunks = compute_nblock(nChars);
    int nStripes = compute_nstripe(nChunks);
    stripe_t * stripes = malloc(sizeof(stripe_t) * nStripes);
    block_t * blocks = malloc(sizeof(block_t) * nChunks);
    block_t temp_blocks[NB_DISK - 1];

    for(i=0;i<nChunks;i++) {
        for(j=0;j<nChars;j++) {
            blocks[i].data[j] = buffer[i * BLOCK_SIZE + j];
        }
    }

    for(i=0;i<nStripes;i++) {
        stripes[i].nblocks = NB_DISK;
        for(j=0;j<NB_DISK-1;j++) {
            temp_blocks[j] = blocks[i * (NB_DISK-1) + j];
        }
        for(j=0;j<NB_DISK;j++) {
            u = 0;
            if(j == compute_parity_index(i)) {
                stripes[i].stripe[j] = compute_parity(temp_blocks, NB_DISK-1);
            } else {
                stripes[i].stripe[j] = blocks[i * (NB_DISK-1) + u];
                u++;
            }
        }
        if(write_stripes(stripes[i], ???, disks))
            return EXIT_FAILURE;
    }
    free(blocks);
    free(stripes);
    return EXIT_SUCCESS;
}

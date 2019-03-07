#include "../headers/utils_stripe.h"

int write_stripes(stripe_t stripe, int pos, FILE ** disks) {
    int i;
    for(i=0;i<stripe.nblocks;i++) {
            if(write_block(stripe.stripe[i], pos, disks[i])) {
                fprintf(stderr, "Erreur lors de l'ecriture de la bande.\n");
                return EXIT_FAILURE;
            }
    }
    return EXIT_SUCCESS;
}

int write_chunk(uchar * buffer, int nChars, int startbyte, FILE ** disks) {
    int i, j, x, u;
    int nChunks = compute_nblock(nChars);
    int nStripes = 3;//compute_nstripe(nChunks);/*64*/
    nChunks = nChunks + nStripes + ((nChunks + nStripes) / NB_DISK);
    nStripes = 4; //compute_nstripe(nChunks);
    block_t *blocks = malloc(sizeof(block_t) * nChunks);
    stripe_t *stripes = malloc(sizeof(stripe_t) * nStripes);
    block_t temp_blocks[NB_DISK - 1];

    for(i=0;i<nChunks;i++) {
        for(j=0;j<BLOCK_SIZE;j++) {
            if((i * BLOCK_SIZE + j) < nChars) {
                blocks[i].data[j] = buffer[i * BLOCK_SIZE + j];
            } else {
                blocks[i].data[j] = '0';
            }
        }
    }
    for(i=0;i<nStripes;i++) {
        u = 0;
        stripes[i].nblocks = NB_DISK;
        stripes[i].stripe = malloc(sizeof(block_t) * NB_DISK);
        for(j=0;j<NB_DISK-1;j++) {
            temp_blocks[j] = blocks[i * (NB_DISK-1) + j];
        }
        for(j=0;j<NB_DISK;j++) {
            if(j == 3/*compute_parity_index(i)*/) {/*if(j==3) {*/
                stripes[i].stripe[j] = blocks[i * (NB_DISK-1) + u];//compute_parity(temp_blocks, NB_DISK-1); /*stripes[i].stripe[j] = blocks[i * (NB_DISK-1) + u];*/
                u++;
            } else {
                stripes[i].stripe[j] = blocks[i * (NB_DISK-1) + u];
                u++;
            }
        }

        if(write_stripes(stripes[i], startbyte + (i * BLOCK_SIZE), disks))
            return EXIT_FAILURE;
    }
    free(blocks);
    free(stripes);
    return EXIT_SUCCESS;
}

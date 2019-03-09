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

block_t *generateStripe(uchar *buffer, int nChars, int *posCurrent, int nb_disks) {
        int i, j;
        block_t *blocks = malloc(sizeof(block_t) * (nb_disks-1));
        for(i=0;i<nb_disks-1;i++) {
            for(j=0;j<BLOCK_SIZE;j++) {
                if(*posCurrent == nChars) {
                    blocks[i].data[j] = '\0';
                } else {
                    blocks[i].data[j] = buffer[(*posCurrent)++];
                }
            }
        }
        return blocks;
}

int compute_final_nblock(int nChars) {
    int nChunks = compute_nblock(nChars);
    int nStripes = 3;//compute_nstripe(nChunks);
    return nChunks + nStripes + ((nChunks + nStripes) / NB_DISK);
}

void print_block(block_t block) {
    int i;
    for(i=0;i<BLOCK_SIZE;i++)
    printf("%c ", block.data[i]);
    printf("\n");
}

void print_stripe(stripe_t stripe) {
    int i, j;
    for(i=0;i<stripe.nblocks;i++)
        print_block(stripe.stripe[i]);
    printf("\n");
}

int write_chunk(uchar * buffer, int nChars, int startbyte, FILE ** disks) {
    int i, j, pos = 0;
    int nChunks = compute_final_nblock(nChars);
    int nStripes = 4;//compute_nstripe(nChunks);
    stripe_t stripe;
    stripe.nblocks = NB_DISK;
    stripe.stripe = malloc(sizeof(block_t) * NB_DISK);

    for(i=0;i<nStripes;i++) {
        block_t *blocks = generateStripe(buffer, nChars, &pos, NB_DISK);
        int i_blocks = 0;

        for(j=0;j<NB_DISK;j++) {
            if(j == 3/*compute_parity_index(i)*/) {
                stripe.stripe[j] = blocks[i_blocks]; //a suppr
                //stripes[i].stripe[j] = compute_parity(blocks, NB_DISK-1);
            } else {
                stripe.stripe[j] = blocks[i_blocks];
                i_blocks++;
            }
        }
        print_stripe(stripe);

        if(write_stripes(stripe, startbyte + (i * BLOCK_SIZE), disks))
            return EXIT_FAILURE;

        free(blocks);
    }
    
    free(stripe.stripe);
    return EXIT_SUCCESS;
}

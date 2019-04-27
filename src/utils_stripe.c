#include "../headers/utils_stripe.h"

int read_chunk(uchar * buffer, int nChars, int startbyte) {
	/// \brief Lis une chaine de caractères du RAID
	/// \param[in] startbyte : Position où lire la chaine en octets
	int posBuffer = 0;
	int posDisk = 0;
	while(posBuffer < nChars) {
		stripe_t stripe;
		read_stripe(&stripe, startbyte + posDisk*BLOCK_SIZE);
		for(int i = 0; i < stripe.nblocks && posBuffer < nChars; i++) {
			block_t block = stripe.stripe[i];
			if(i != compute_parity_index(startbyte + posDisk)) {
				for(int j = 0; j < BLOCK_SIZE && posBuffer < nChars; j++) {
					buffer[posBuffer] = block.data[j];
					posBuffer++;
				}
			}
		}
		posDisk++;
	}
	return posDisk;
}

int read_stripe(stripe_t *stripe, uint pos){
	/**
	* \brief Lecture d'une bande de bloc à une position donné sur le disque virtuel.
	* \param[in] stripe : bande dans laquelle la bande lu sur le disque sera retourné.
	  	       pos : position de la bande sur le disque.
		       disk : ensemble des disques representants le disque virtuel.
	* \param[out] boolean : 0 = Ack, !0 = Nack.
	*/
	stripe->nblocks = r5Disk.ndisk;
	stripe->stripe = malloc((r5Disk.ndisk)* sizeof(block_t));

	for(int i = 0; i < r5Disk.ndisk; i++) {
		if (read_block(&(stripe->stripe[i]), pos , r5Disk.storage[i])) {
			printf("erreur de lecture [read_block]\n");
			return 1;
		}
	}
	return 0;
}

int write_stripe(stripe_t stripe, int pos) {
    /// \brief Ecrit une bande sur le système RAID à une position donnée
    /// \param[in] stripe : Bande à écrire sur le disk
    /// \param[in] pos : Position où écrire le block
    /// \return 0 s'il n'y a pas eu d'erreur, 1 dans le cas contraire
    int i;
    for(i=0;i<stripe.nblocks;i++) {
            if(write_block(stripe.stripe[i], pos, r5Disk.storage[i])) {
                fprintf(stderr, "Erreur lors de l'ecriture de la bande.\n");
                return EXIT_FAILURE;
            }
    }
    return EXIT_SUCCESS;
}

block_t *generateStripe(uchar *buffer, int nChars, int *posCurrent) {
    /// \brief Transforme une partie d'une chaine de caractères en nb_disks - 1 blocks.
    /// \brief Incrémente posCurrent de façon automatique.
    /// \param[in] buffer : Chaine de caractères
    /// \param[in] nChars : Nombre de caractères de la chaine
    /// \param[in, out] posCurrent : Curseur dans la chaine de caractères
    /// \return Un pointeur de blocks
    int i, j;
    block_t *blocks = malloc(sizeof(block_t) * (r5Disk.ndisk-1));
    for(i=0;i<r5Disk.ndisk-1;i++) {
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
    /// \brief Calcule le nombre de blocks à écrire sur le disque.
    /// \brief Prend en compte les blocks de parités.
    /// \param[in] nChars : Nombre de caractères de la chaine à écrire
    /// \return Le nombre de blocks
    int nChunks = compute_nblock(nChars);
    int nStripes = compute_nstripe(nChunks);
    return nChunks + nStripes + ((nChunks + nStripes) / r5Disk.ndisk);
}

void print_stripe(stripe_t stripe) {
    int i;
    for(i=0;i<stripe.nblocks;i++)
        print_block(stripe.stripe[i]);
    printf("\n");
}

int write_chunk(uchar * buffer, int nChars, int startbyte) {
    /// \brief Ecrit une chaine de caractères sur le système RAID.
    /// \param[in] buffer : Chaine de caractères à écrire
    /// \param[in] nChars : Nombre de caractères de la chaine
    /// \param[in] startbyte : Position où écrire la chaine en octets
    /// \return Le nombre de bandes écrites ou -1 s'il y a eu une erreur.
    int i, j, pos = 0;
    int nChunks = compute_nblock(nChars);
    int nStripes = compute_nstripe(nChunks);
    stripe_t stripe;
    stripe.nblocks = r5Disk.ndisk;
    stripe.stripe = malloc(sizeof(block_t) * r5Disk.ndisk);

    for(i=0;i<nStripes;i++) {
        block_t *blocks = generateStripe(buffer, nChars, &pos);
        int i_blocks = 0;
        for(j=0;j<r5Disk.ndisk;j++) {
            if(j == compute_parity_index(i)) {
                stripe.stripe[j] = compute_parity(blocks, r5Disk.ndisk-1);
            } else {
                stripe.stripe[j] = blocks[i_blocks];
                i_blocks++;
            }
        }
        if(write_stripe(stripe, startbyte + (i * BLOCK_SIZE)))
            return -1;

        free(blocks);
    }

    free(stripe.stripe);
    return nStripes;
}

int compute_parity_index(int numBande){
    /**
    * \brief Indique le disque sur lequel se trouve le bloc de parité.
    * \param[in] i : Position sur le disque virtuel.
    * \param[out] indPar : Numéro du disque où se situera le bloc de parité.
    */
    return (r5Disk.ndisk - 1) - (numBande % r5Disk.ndisk);
}


int compute_nstripev1(int nb_blocks) {
    return nb_blocks / (r5Disk.ndisk - 1) + ((nb_blocks / (r5Disk.ndisk - 1)) % 2 != 0);
}

int compute_nstripe(int nb_blocks) {
	int nb_block_parite = (nb_blocks / (r5Disk.ndisk - 1)) + (nb_blocks % (r5Disk.ndisk - 1) != 0);
	if((nb_block_parite + nb_blocks) % r5Disk.ndisk == 0)
		return (nb_block_parite + nb_blocks) / r5Disk.ndisk;
	return (nb_block_parite + nb_blocks + (r5Disk.ndisk - (nb_blocks + nb_block_parite) % r5Disk.ndisk)) / r5Disk.ndisk;
}

block_t xor(block_t a, block_t b) {
    block_t c;
    for(int i = 0; i < BLOCK_SIZE; i++) {
        c.data[i] = a.data[i] ^ b.data[i];
    }
    return c;
}

block_t compute_parity(block_t *blocks, int nb_block) {
    block_t parite = create_block();
    for(int i = 0; i < nb_block; i++) {
        parite = xor(parite, blocks[i]);
    }
    return parite;
}

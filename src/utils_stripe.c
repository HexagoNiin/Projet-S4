#include "../headers/utils_stripe.h"

int read_chunk(uchar * buffer, int nChars, int startbyte) {
	if(r5Disk.super_block.raid_type == ZERO)
		return read_chunk_raid0(buffer, nChars, startbyte);
	if(r5Disk.super_block.raid_type == UN)
		return read_chunk_raid1(buffer, nChars, startbyte);
<<<<<<< HEAD
	if(r5Disk.super_block.raid_type == CINQUANTE)
		return read_chunk_raid50(buffer, nChars, startbyte);
=======
>>>>>>> ac7e15c2497d3d8491cef6a0ebf7990fce4e0ea6
	else
		return read_chunk_raid5(buffer, nChars, startbyte);
}

int read_chunk_raid5(uchar * buffer, int nChars, int startbyte) {
<<<<<<< HEAD
=======
	/// \brief Lis une chaine de caractères du RAID
	/// \param[out] buffer : Chaine de caractere lue
	/// \param[in] nChars : Nombre de caracteres a lire
	/// \param[in] startbyte : Position où lire la chaine en octets
	log4("[READ_CHUNK] RAID CINQ");
	int posBuffer = 0;
	int posDisk = 0;
	while(posBuffer < nChars) {
		stripe_t stripe;
		if(read_stripe(&stripe, startbyte + posDisk*BLOCK_SIZE)) {
			log4("[READ_CHUNK] Erreur lecture du chunk");
			free(stripe.stripe);
			return -1;
		}
		int parity_index = compute_parity_index(startbyte / r5Disk.ndisk + posDisk, r5Disk.ndisk);
		for(int i = 0; i < stripe.nblocks && posBuffer < nChars; i++) {
			block_t block = stripe.stripe[i];
			if(i != parity_index) {
				for(int j = 0; j < BLOCK_SIZE && posBuffer < nChars; j++) {
					buffer[posBuffer] = block.data[j];
					posBuffer++;
				}
			}
		}
		posDisk++;
		free(stripe.stripe);
	}
	return posDisk;
}

int read_chunk_raid1(uchar * buffer, int nChars, int startbyte) {
>>>>>>> ac7e15c2497d3d8491cef6a0ebf7990fce4e0ea6
	/// \brief Lis une chaine de caractères du RAID
	/// \param[out] buffer : Chaine de caractere lue
	/// \param[in] nChars : Nombre de caracteres a lire
	/// \param[in] startbyte : Position où lire la chaine en octets
	log4("[READ_CHUNK] RAID CINQ");
	int posBuffer = 0;
	int posDisk = 0;
	while(posBuffer < nChars) {
		stripe_t stripe;
		if(read_stripe(&stripe, startbyte + posDisk*BLOCK_SIZE)) {
			log4("[READ_CHUNK] Erreur lecture du chunk");
			free(stripe.stripe);
			return -1;
		}
		int parity_index = compute_parity_index(startbyte / r5Disk.ndisk + posDisk, r5Disk.ndisk);
		for(int i = 0; i < stripe.nblocks && posBuffer < nChars; i++) {
			block_t block = stripe.stripe[i];
			if(i != parity_index) {
				for(int j = 0; j < BLOCK_SIZE && posBuffer < nChars; j++) {
					buffer[posBuffer] = block.data[j];
					posBuffer++;
				}
			}
		}
		posDisk++;
		free(stripe.stripe);
	}
	return posDisk;
}

int read_chunk_raid0(uchar * buffer, int nChars, int startbyte) {
	/// \brief Lis une chaine de caractères du RAID
	/// \param[out] buffer : Chaine de caractere lue
	/// \param[in] nChars : Nombre de caracteres a lire
	/// \param[in] startbyte : Position où lire la chaine en octets
	log4("[READ_CHUNK] RAID ZERO");
	int posBuffer = 0;
	int posDisk = 0;
	while(posBuffer < nChars) {
		stripe_t stripe;
		if(read_stripe(&stripe, startbyte + posDisk*BLOCK_SIZE)) {
			log4("[READ_CHUNK] Erreur lecture du chunk");
			free(stripe.stripe);
			return -1;
		}
		for(int i = 0; i < stripe.nblocks && posBuffer < nChars; i++) {
			for(int j = 0; j < BLOCK_SIZE && posBuffer < nChars; j++) {
				buffer[posBuffer] = stripe.stripe[i].data[j];
				posBuffer++;
			}
		}
		posDisk++;
		free(stripe.stripe);
	}
	return posDisk;
}

int read_chunk_raid50(uchar * buffer, int nChars, int startbyte) {
	/// \brief Lis une chaine de caractères du RAID
	/// \param[out] buffer : Chaine de caractere lue
	/// \param[in] nChars : Nombre de caracteres a lire
	/// \param[in] startbyte : Position où lire la chaine en octets
	log4("[READ_CHUNK] RAID CINQUANTE");
	int posBuffer = 0;
	int posDisk = 0;
	log4("[READ_CHUNK] nChars : %d", nChars);
	while(posBuffer < nChars) {
		log4("[READ_CHUNK] posBuffer : %d", posBuffer);
		stripe_t stripe;
		if(read_stripe(&stripe, startbyte + posDisk*BLOCK_SIZE)) {
			log4("[READ_CHUNK] Erreur lecture du chunk");
			free(stripe.stripe);
			return -1;
		}
		
		int parity_index = compute_parity_index(startbyte / r5Disk.ndisk + posDisk, 3);
		for(int i = 0; i < stripe.nblocks && posBuffer < nChars; i++) {
			block_t block = stripe.stripe[i];
			if(i % 3 != parity_index) {
				for(int j = 0; j < BLOCK_SIZE && posBuffer < nChars; j++) {
					buffer[posBuffer] = block.data[j];
					posBuffer++;
				}
			}
		}
		posDisk++;
		free(stripe.stripe);
	}
	return posDisk;
}


int read_chunk_raid1(uchar * buffer, int nChars, int startbyte) {
	log4("[READ_CHUNK] RAID UN");
	(void)buffer;
	(void)nChars;
	(void)startbyte;
	return 0;
}


int read_stripe(stripe_t *stripe, uint pos) {
	/**
	* \brief Lecture d'une bande de bloc à une position donné sur le disque virtuel.
	* \param[in] stripe : bande dans laquelle la bande lu sur le disque sera retourné.
	  	       pos : position de la bande sur le disque en octet.
		       disk : ensemble des disques representants le disque virtuel.
	* \param[out] boolean : 0 = Ack, !0 = Nack.
	*/
	stripe->nblocks = r5Disk.ndisk;
	stripe->stripe = malloc((r5Disk.ndisk)* sizeof(block_t));
	for(int i = 0; i < r5Disk.ndisk; i++) {
		if (read_block(&(stripe->stripe[i]), pos, r5Disk.storage[i])) {
			log4("[READ_STRIPE] Erreur de lecture du bloc\n");
			return EXIT_FAILURE;
		}
	}
	return EXIT_SUCCESS;
}

int write_stripe(stripe_t stripe, int pos) {
    /// \brief Ecrit une bande sur le système RAID à une position donnée
    /// \param[in] stripe : Bande à écrire sur le disk
    /// \param[in] pos : Position où écrire le block en octet
    /// \return 0 s'il n'y a pas eu d'erreur, 1 dans le cas contraire
    int i;
    for(i=0;i<stripe.nblocks;i++) {
            if(write_block(stripe.stripe[i], pos, r5Disk.storage[i])) {
                log4("[WRITE_STRIPE] Erreur lors de l'ecriture de la bande.\n");
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
	int size;
	if(r5Disk.raidmode == CINQ)
	 	size = r5Disk.ndisk - 1;
	else if(r5Disk.raidmode == CINQUANTE)
		size = r5Disk.ndisk - 2; // -grappe
	else
		size = r5Disk.ndisk;
    block_t *blocks = malloc(sizeof(block_t) * (size));
	log4("[GENERATE_STRIPE] size : %d", size);
    for(i=0;i<size;i++) {
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

int write_chunk(uchar * buffer, int nChars, int startbyte) {
	if(r5Disk.super_block.raid_type == ZERO)
		return write_chunk_raid0(buffer, nChars, startbyte);
	if(r5Disk.super_block.raid_type == UN)
		return write_chunk_raid1(buffer, nChars, startbyte);
	if(r5Disk.super_block.raid_type == CINQUANTE)
		return write_chunk_raid50(buffer, nChars, startbyte);
	else
		return write_chunk_raid5(buffer, nChars, startbyte);
}

int write_chunk_raid5(uchar * buffer, int nChars, int startbyte) {
	/// \brief Ecrit une chaine de caractères sur le système RAID.
	/// \param[in] buffer : Chaine de caractères à écrire
	/// \param[in] nChars : Nombre de caractères de la chaine
	/// \param[in] startbyte : Position où écrire la chaine en octets
	/// \return Le nombre de bandes écrites ou -1 s'il y a eu une erreur.
	log4("[WRITE_CHUNK] RAID CINQ");
	int i, j, pos = 0;
	int nChunks = compute_nblock(nChars);
	int nStripes = compute_nstripe(nChunks);
	stripe_t stripe;
	stripe.nblocks = r5Disk.ndisk;
	stripe.stripe = malloc(sizeof(block_t) * r5Disk.ndisk);

	for(i=0;i<nStripes;i++) {
		block_t *blocks = generateStripe(buffer, nChars, &pos);
		int i_blocks = 0;
		int index = compute_parity_index(i + (startbyte / r5Disk.ndisk), r5Disk.ndisk);
		for(j=0;j<r5Disk.ndisk;j++) {
			if(j == index) {
				stripe.stripe[j] = compute_parity(blocks, r5Disk.ndisk-1);
			} else {
				stripe.stripe[j] = blocks[i_blocks];
				i_blocks++;
			}
		}
		if(write_stripe(stripe, startbyte + (i * BLOCK_SIZE))) {
			log4("[WRITE_CHUNK] : Erreur ecriture stripe");
			return -1;
		}

		free(blocks);
	}

	free(stripe.stripe);
	return nStripes;
}

int write_chunk_raid1(uchar * buffer, int nChars, int startbyte) {
	/// \brief Ecrit une chaine de caractères sur le système RAID.
	/// \param[in] buffer : Chaine de caractères à écrire
	/// \param[in] nChars : Nombre de caractères de la chaine
	/// \param[in] startbyte : Position où écrire la chaine en octets
	/// \return Le nombre de bandes écrites ou -1 s'il y a eu une erreur.
	log4("[WRITE_CHUNK] RAID UN");
	int nblocks = compute_nblock(nChars);
	stripe_t s;
	s.nblocks = r5Disk.ndisk;
	s.stripe = malloc(sizeof(block_t) * r5Disk.ndisk);
	for(int i = 0; i < nblocks; i++) {
		for(int j = 0; j < r5Disk.ndisk; j++) {
			for(int k = 0; k < BLOCK_SIZE; i++) {
				s.stripe[j].data[k] = buffer[i * BLOCK_SIZE + j * r5Disk.ndisk];
			}
		}
		if(write_stripe(s, i * BLOCK_SIZE)) return -1;
	}
	return nblocks;
}

int write_chunk_raid50(uchar * buffer, int nChars, int startbyte) {
	/// \brief Ecrit une chaine de caractères sur le système RAID.
	/// \param[in] buffer : Chaine de caractères à écrire
	/// \param[in] nChars : Nombre de caractères de la chaine
	/// \param[in] startbyte : Position où écrire la chaine en octets
	/// \return Le nombre de bandes écrites ou -1 s'il y a eu une erreur.
	log4("[WRITE_CHUNK] RAID CINQUANTE");
	stripe_t stripe;
	stripe.nblocks = r5Disk.ndisk;
	stripe.stripe = malloc(sizeof(block_t) * r5Disk.ndisk);
	int i, j, u, pos = 0;
	int nChunks = compute_nblock(nChars);
	int nStripes = compute_nstripe(nChunks);
	int taille_grappe = 3, nombre_grappe = 2;
	int i_blocks;
	log4("[WRITE_CHUNK] nChunks : %d nStripe : %d", nChunks, nStripes);
	for(i=0;i<nStripes;i++) {
		block_t *blocks = generateStripe(buffer, nChars, &pos);
		int index = compute_parity_index(i + (startbyte / r5Disk.ndisk), taille_grappe);
		block_t *blocks_par_grappe = malloc(sizeof(block_t) * (taille_grappe - 1));
		for(u=0;u<nombre_grappe;u++) {
			for(j=0;j<taille_grappe - 1;j++)
				blocks_par_grappe[j] = blocks[u * (taille_grappe - 1) + j];
			i_blocks = 0;
			for(j=0;j<taille_grappe;j++) {
				if(j == index) {
					stripe.stripe[u * taille_grappe + j] = compute_parity(blocks_par_grappe, taille_grappe-1);
		//			printf("parite\n");
		//			print_block(stripe.stripe[u * taille_grappe + j]);
				} else {
					stripe.stripe[u * taille_grappe + j] = blocks_par_grappe[i_blocks];
					i_blocks++;
		//			print_block(stripe.stripe[u * taille_grappe + j]);
				}
			}
		}
		printf("Position : %d\n", startbyte + (i * BLOCK_SIZE));
		print_block(stripe.stripe[0]);
		print_block(stripe.stripe[1]);
		print_block(stripe.stripe[2]);
		print_block(stripe.stripe[3]);
		print_block(stripe.stripe[4]);
		print_block(stripe.stripe[5]);
		if(write_stripe(stripe, startbyte + (i * BLOCK_SIZE))) {
			log4("[WRITE_CHUNK] : Erreur ecriture stripe");
			return -1;
		}
	}
	return nStripes;
}

int write_chunk_raid0(uchar *buffer, int nChars, int startbyte) {
	log4("[WRITE_CHUNK] RAID ZERO");
	int nBlock = compute_nblock(nChars);
	int nStripes = compute_nstripe(nBlock);
	int pos = 0;
	int i;
	stripe_t stripe;
	stripe.nblocks = r5Disk.ndisk;
	for(i=0;i<nStripes;i++) {
        stripe.stripe = generateStripe(buffer, nChars, &pos);
        if(write_stripe(stripe, startbyte + (i * BLOCK_SIZE))) {
			log4("[WRITE_CHUNK] : Erreur ecriture stripe");
            return -1;
		}
		free(stripe.stripe);
    }
    return nStripes;
}

int compute_parity_index(int numBande, int ndisk){
    /**
    * \brief Indique le disque sur lequel se trouve le bloc de parité.
    * \param[in] i : Position sur le disque virtuel.
    * \param[out] indPar : Numéro du disque où se situera le bloc de parité.
    */
    return (ndisk - 1) - (numBande % ndisk);
}

int compute_nstripe(int nb_blocks) {
	if(r5Disk.raidmode == CINQ)
    	return nb_blocks / (r5Disk.ndisk - 1) + (nb_blocks % (r5Disk.ndisk - 1) != 0);
	else if(r5Disk.raidmode == CINQUANTE)
		return nb_blocks / (r5Disk.ndisk - 2) + (nb_blocks % (r5Disk.ndisk - 2) != 0); // -4 => -grappe
	else
		return nb_blocks / r5Disk.ndisk + (nb_blocks % r5Disk.ndisk != 0);
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

#include "../headers/utils_block.h"

block_t create_block() { //Utilisé dans utils_stripe.c
	/// \brief Crée un block vide
    /// \return Un block initialisé à 0
	block_t block; //Block renvoyé
    for(int i = 0; i < BLOCK_SIZE; i++) { //Initialisation du block de parité
        block.data[i] = 0;
    }
	return block;
}

int compute_nblock(int nb_octets) {
    /// \brief Calcule le nombre de blocks nécessaires pour stocker nb_octets octets
    /// \param[in] nb_octets : Nombre d'octets à stocker
    /// \return Nombre de blocks nécessaires
	return nb_octets / BLOCK_SIZE + (nb_octets % BLOCK_SIZE != 0);
}

int write_block(block_t block, int pos, FILE * disk_id) {
    /// \brief Ecrit un block sur un disque à une position donnée
    /// \param[in] block : Block à écrire sur le disk
    /// \param[in] pos : Position où écrire le block
    /// \param[in] disk_id : Disk sur lequel écrire le block
    /// \return Un entier indiquant si l'opération s'est bien passée
    fseek(disk_id, pos, SEEK_SET);
    if(fwrite(&block, sizeof(block_t), 1, disk_id) != 1) {
        fprintf(stderr, "Une erreur est survenue lors de l'ecriture du block.\n");
        return EXIT_FAILURE; //1
    }
    return EXIT_SUCCESS; //0
}

void print_block(block_t block) {
    int i;
    for(i=0;i<BLOCK_SIZE;i++)
    printf("%c ", block.data[i]);
    printf("\n");
}

int block_repair(int pos, int id_disk) {
    /// \brief Répare un block erroné
    /// \param[in] pos : Position du block eronné
    /// \param[in] disk_id : Index du disk avec le block eronné
    /// \return Un entier indiquant si l'opération s'est bien passée
    int i, j;
	block_t block;
    block_t block_repare;
    for(i=0;i<r5Disk.ndisk;i++) {
        if(i != id_disk) {
            if(!read_block(&block, pos, r5Disk.storage[i])) {
                fprintf(stderr, "Une erreur est survenue, il y a au moins deux blocks qui ont ete corrompus.\n");
                return 1;
            }
            for(j=0;j<BLOCK_SIZE;j++)
                block_repare.data[j] ^= block.data[j];
        }
    }
    if(!write_block(block_repare, pos, r5Disk.storage[id_disk])) {
        return 0;
    } return 2;
}

int read_block (block_t *block, uint pos /*position d'un block*/ , FILE *disk) {
	/**
	* \brief Lit le bloc à une position sur un disque.
   	* \param[in] *block : Pointeur du bloc dans lequel on rend la lecture.
		     pos : Position du bloc.
   		     disk : Disque dans lequel on lit.
    	* \param[out] Un entier indiquant si l'opération s'est bien passée.
	*/
	uchar c;
	int i;

	/*for (i = 0; i < (pos * BLOCK_SIZE); i++){ //offset
		c = fgetc(disk);

		if (c == EOF)
			return(1);//inaccessible
	}*/
	fseek(disk, pos, SEEK_SET);

	for (i = 0; i < BLOCK_SIZE; i ++){
		c = fgetc(disk);

		if (c == EOF)
			return(1);//inaccessible

		block->data[i] = c;
	}
	return(0);
}

char* itoh(int x) {
	/**
	* \brief Converti un entier en hexadécimal.
	* \param[in] x : entier à convertir.
	* \param[out] h : hexadécimal converti.
	*/


	char *h;
	h = malloc(2 * sizeof(char));
	sprintf(h, "%x", x);
	return h;
}

void display_block(block_t block) {
	/**
	* \brief Affiche en hexadecimal le contenu du bloc sur la console.
	* \param[in]  block : bloc dont le contenu sera affiché.
	* \param[out] 0 = Ack, !0 = Nack.
	*/

	int i;
	char *byteHex;

	for(i = 0; i < BLOCK_SIZE; i++){

		byteHex = itoh(block.data[i]);

		if (block.data[i] <= 9)
		printf("0");
		printf("%s ", byteHex);

	}

	printf("\n");
}

int display_pos(uint pos, FILE* disk) {
	/**
	* \brief Affiche en hexadecimal le contenu du bloc sur une position et sur un disque donné sur la console.
	* \param[in]  pos : position du bloc sur le disque.
		      disk : disque sur lequel on souhaite lire le bloc.
	* \param[out] 0 = Ack, !0 = Nack.
	*/

	block_t block;

	if (read_block(&block, pos, disk)){
		printf("erreur de lecture [read_block]\n");
		return 1;
	}

	display_block(block);

	return 0;
}

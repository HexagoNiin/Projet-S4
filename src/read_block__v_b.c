#include "../headers/utils_block.h"

int read_block (block_t *block, uint pos /*position d'un block*/ , FILE *disk){
	/**
	*	\fn int block_read (block_t *block, uint pos, FILE disk)
	*	\brief Lit le bloc à une position sur un disque
    *	\param[in] *block : Pointeur du bloc dans lequel on rend la lecture
    *	\param[in] pos : Position du bloc
    *	\param[in] disk : Disque dans lequel on lit
    *	\return Un entier indiquant si l'opération s'est bien passée
	*/

	uchar c;

	int i;
	for (i = 0; i < (pos * BLOCK_SIZE) - 1; i++){ //offset
		c= fgetc(disk);

		if (c == EOF)
			return(1);//inaccessible
	}

	for (i = 0; i < BLOCK_SIZE; i ++){
		c = fgetc(disk);

		if (c == EOF)
			return(1);//inaccessible

		if (&c == NULL) //NULL c'est pour un pointeur, or là tu travailles avec un char, pour le moment j'ai changé c en &c
			return(2);//repare aled destruction de donnée

		block->data[i] = c;
	}

	return(0);
}

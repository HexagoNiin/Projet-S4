#include "../headers/utils_inode.h"

void delete_inode(int pos){
	/**
    * \brief Supprime un noeud sur la table des index.
    * \param[in] pos : position du noeud à supprimer.
    */

	/* supprime l'inode */
	r5Disk.inodes[pos].first_byte = 0;

	/* regroupe les inodes */
	int i;
	for(i=pos; i < INODE_TABLE_SIZE-1; i++)
		r5Disk.inodes[i] = r5Disk.inodes[i+1];
}

int inodelen() {
	inode_t inode = {"", 0, 0, 0};
	return snprintf(NULL, 0, "%s%u%u%u", inode.filename, inode.size, inode.first_byte, inode.nblock);
}

uchar *indtostr(inode_t inode) {
    /// \brief Transforme une inode en chaine de caractères non signés.
    /// \param[in] inode : L'inode a transformer
	/// \return La chaine de caractères ou NULL s'il y a eu une erreur

	/* recuperer taille inode */
	int len = inodelen();

	if(len > MAX_MSG) {
		fprintf(stderr, "L'inode ne peut pas etre convertie en string.\n");
		return NULL;
	}

	/* copie filename */
	char *str = malloc(sizeof(char) * len);
	int i, strPos = 0;
    for(i=0;i<FILENAME_MAX_SIZE;i++) {
        str[strPos] = inode.filename[i];
        strPos++;
    }
	/* copie size */
    if((strPos += sprintf(&str[strPos], "%u", inode.size)) < 0) {
        fprintf(stderr, "Il y a eu un probleme lors de l'ecriture de l'element size.\n");
        return NULL;
    }
	/* copie first_byte */
    if((strPos += sprintf(&str[strPos], "%u", inode.nblock)) < 0) {
        fprintf(stderr, "Il y a eu un probleme lors de l'ecriture de l'element nblock.\n");
        return NULL;
    }
	/* copie nblock */
    if((strPos += sprintf(&str[strPos], "%u", inode.first_byte)) < 0) {
        fprintf(stderr, "Il y a eu un probleme lors de l'ecriture de l'element first_byte.\n");
        return NULL;
    }

    return (uchar*)str;
}

int write_inodes_table(int startbyte) {
    /// \brief Ecrit la table d'inode sur le système RAID.
    /// \param[in] startbyte : position
    /// \return 0 si tout s'est bien passé, 1 s'il y a eu une erreur lors du cast de la table, 2 s'il y a eu erreur lors de l'écriture
    int i, nStripe = 0;
    for(i=0;i<INODE_TABLE_SIZE;i++) {
        uchar *buffer = indtostr(r5Disk.inodes[i]);
        if(buffer == NULL) {
            fprintf(stderr, "Erreur lors du cast de l'inode en string.\n");
            return 1;
        }
        /* startbyte ici est provisoire */
        if((nStripe = write_chunk(buffer, inodelen(), startbyte + (i * nStripe))) == -1) {
            fprintf(stderr, "Erreur lors de l'ecriture d'une inode.\n");
            return 2;
        }
    }
    return EXIT_SUCCESS;
}

int get_unused_inode() {
    /// \brief Retourne l'indice du premier inode disponible dans la table.
    /// \return L'indice d'un inode ou -1 si la table est pleine
    int i;
    for(i=0;i<INODE_TABLE_SIZE;i++) {
        if(r5Disk.inodes[i].first_byte == 0)
            return i;
    }
    return -1;
}

int sblen() {
	return snprintf(NULL, 0, "%u%u%u", r5Disk.super_block.raid_type, r5Disk.super_block.nb_blocks_used, r5Disk.super_block.first_free_byte);
}

uchar *sbtostr() {
	/// \brief Transforme la structure super_block_t en chaine de caractères
	/// \return la chaine de caractères

	/* recupere taille super block */
	int len = sblen();

	if(len > MAX_MSG) {
		fprintf(stderr, "Le super block ne peut pas etre convertie en string.\n");
		return NULL;
	}

	char *str = malloc(sizeof(char) * len);
	int strPos = 0;
	/* copie raid_type */
	if((strPos += sprintf(&str[strPos], "%u", r5Disk.super_block.raid_type)) < 0) {
		fprintf(stderr, "Il y a eu un probleme lors de l'ecriture de l'element raid_type.\n");
		return NULL;
	}
	/* copie nb_blocks_used */
	if((strPos += sprintf(&str[strPos], "%u", r5Disk.super_block.nb_blocks_used)) < 0) {
		fprintf(stderr, "Il y a eu un probleme lors de l'ecriture de l'element nb_block_used.\n");
		return NULL;
	}
	/* copie first_free_byte */
	if((strPos += sprintf(&str[strPos], "%u", r5Disk.super_block.first_free_byte)) < 0) {
		fprintf(stderr, "Il y a eu un probleme lors de l'ecriture de l'element first_free_byte.\n");
		return NULL;
	}

    return (uchar*)str;
}

int write_super_block(int *startbyte) {
    uchar *buffer = sbtostr(r5Disk.super_block);

    if(buffer == NULL) {
        fprintf(stderr, "Erreur lors du cast du super block en string.\n");
        return 1;
    }

    if((*startbyte = write_chunk(buffer, sblen(), 0)) == -1) {
        fprintf(stderr, "Erreur lors de l'ecriture du super block.\n");
        return 2;
    }

    return 0;
}

int read_inodes_table() {
    return 0;
}

inode_t init_inode(char *filename, uint size, uint position) {
	inode_t inode;
	strcpy(inode.filename, filename);
	inode.size = size;
	inode.first_byte = position;
	return inode;
}

int update_inodes_table(inode_t inode) {
	if(r5Disk.number_of_files < INODE_TABLE_SIZE) {
		r5Disk.inodes[get_unused_inode()] = inode;
		r5Disk.number_of_files++;
		update_first_free_byte(inode.first_byte);
		return 0;
	} else {
		fprintf(stderr, "Erreur, la table d'inodes est pleine, le fichier n'a pas ete ajoute.\n");
		return 1;
	}
}

void update_first_free_byte(int new_byte) {
	r5Disk.super_block.first_free_byte += new_byte;
}

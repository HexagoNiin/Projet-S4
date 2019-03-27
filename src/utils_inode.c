#include "../headers/utils_inode.h"

int delete_inode(inode_table_t *inodeTable, int pos){
	/**
    * \brief Supprime un noeud sur la table des index.
    * \param[in] inodeTable : Table des index du disque virtuel qui sera modifiée et retournée.
                 pos : position du noeud à supprimer.
    * \param[out] 0 = Ack, !0 = Nack;
    */
    
    /* delete du filename ... utile? */
	for (int i = 1; i < FILENAME_MAX_SIZE; i++){
		inodeTable[pos]->filename[i] = 0;
	}
	inodeTable[pos]->filename[0] = '\0';
	
	/* delete size */
	inodeTable[pos]->size = 0;
	
	/* delete nblock */
	inodeTable[pos]->nblock = 0;
	
	/* delete first_byte */
	inodeTable[pos]->first_byte = 0;
	
	for (int i = pos + 1; i < INODE_TABLE_SIZE; i++ {
		inodeTable[i-1] = inodeTable[i];
	}
         
    return 0;
}

uchar *indtostr(inode_t inode) {
    /// \brief Transforme une inode en chaine de caractères.
    /// \param[in] inode : L'inode a transformer
    /// \return La chaine de caractères ou NULL s'il y a eu une erreur
    if(sizeof(inode_t) > MAX_MSG) {
        fprintf(stderr, "L'inode ne peut pas etre convertie en string.\n");
        return NULL;
    }

    char *str = malloc(sizeof(char) * sizeof(inode_t));
    int i, strPos = 0;
    for(i=0;i<FILENAME_MAX_SIZE;i++) {
        str[strPos] = inode.filename[i];
        strPos++;
    }

    if((strPos += sprintf(&str[strPos], "%d", inode.size)) < 0) {
        fprintf(stderr, "Il y a eu un probleme lors de l'ecriture dans la string.\n");
        return NULL;
    }

    if((strPos += sprintf(&str[strPos], "%d", inode.nblock)) < 0) {
        fprintf(stderr, "Il y a eu un probleme lors de l'ecriture dans la string.\n");
        return NULL;
    }

    if((strPos += sprintf(&str[strPos], "%d", inode.first_byte)) < 0) {
        fprintf(stderr, "Il y a eu un probleme lors de l'ecriture dans la string.\n");
        return NULL;
    }

    return (uchar*)str;
}

int write_inodes_table(inode_table_t inodes, FILE **files) {
    /// \brief Ecrit la table d'inode sur le système RAID.
    /// \param[in] inodes : La table d'inodes
    /// \param[in, out] files : Le système RAID
    /// \return 0 si tout s'est bien passé, 1 s'il y a eu une erreur lors du cast de la table, 2 s'il y a eu erreur lors de l'écriture
    int i, nStripe = 0;
    for(i=0;i<INODE_TABLE_SIZE;i++) {
        uchar *buffer = indtostr(inodes[i]);
        if(buffer == NULL) {
            fprintf(stderr, "Erreur lors du cast de l'inode en string.\n");
            return 1;
        }
        if((nStripe = write_chunk(buffer, sizeof(inode_t), INODE_TABLE_SIZE + (i * nStripe), files)) == -1) {
            fprintf(stderr, "Erreur lors de l'ecriture d'une inode.\n");
            return 2;
        }
    }
    return EXIT_SUCCESS;
}

int get_unused_inode(inode_table_t inodes) {
    /// \brief Retourne l'indice du premier inode disponible dans la table.
    /// \param[in] inodes : Table d'inodes
    /// \return L'indice d'un inode ou -1 si la table est pleine
    int i;
    for(i=0;i<INODE_TABLE_SIZE;i++) {
        if(inodes[i].first_byte == 0) {
            return i;
        }
    }
    return -1;
}

int read_inodes_table(table, raid) {
    return 0;
}

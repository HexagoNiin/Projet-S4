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

uchar *indtostr(inode_t inode) {
    /// \brief Transforme une inode en chaine de caractères non signés.
    /// \param[in] inode : L'inode a transformer
	/// \return La chaine de caractères ou NULL s'il y a eu une erreur
	unsigned char *str = malloc(sizeof(inode_t) * sizeof(unsigned char));
	memcpy(str, &inode.filename, sizeof(inode.filename));
	int i = (int)sizeof(inode.filename);
	memcpy(&str[i], &inode.size, sizeof(uint));
	i += (int)sizeof(uint);
	memcpy(&str[i], &inode.first_byte, sizeof(uint));
	i += (int)sizeof(uint);
	memcpy(&str[i], &inode.nblock, sizeof(uint));
    return str;
}

int write_inodes_table(int startbyte) {
    /// \brief Ecrit la table d'inode sur le système RAID.
    /// \param[in] startbyte : position
    /// \return 0 si tout s'est bien passé, 1 s'il y a eu une erreur lors du cast de la table, 2 s'il y a eu erreur lors de l'écritureZ
    int i, nStripe = 0;
	uchar *buffer = NULL;
    for(i=0;i<INODE_TABLE_SIZE;i++) {
        buffer = indtostr(r5Disk.inodes[i]);
        if((nStripe = write_chunk(buffer, sizeof(inode_t), startbyte + (i * nStripe))) == -1) {
            fprintf(stderr, "Erreur lors de l'ecriture d'une inode.\n");
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

inode_t strtoind(uchar *str) {
	inode_t inode;
	memcpy(&inode.filename, str, sizeof(inode.filename));
	int i = (int)sizeof(inode.filename);
	memcpy(&inode.size, &str[i], sizeof(uint));
	i += (int)sizeof(uint);
	memcpy(&inode.first_byte, &str[i], sizeof(uint));
	i += (int)sizeof(uint);
	memcpy(&inode.nblock, &str[i], sizeof(uint));
    return inode;
}

int read_inodes_table(int startbyte) {
	int i, nStripe;
	uchar *buffer = malloc(sizeof(uchar) * sizeof(inode_t));
	for(i=0;i<INODE_TABLE_SIZE;i++) {
		if((nStripe = read_chunk(buffer, sizeof(inode_t), startbyte + (i * nStripe))) == -1) {
			fprintf(stderr, "Erreur lors de la lecture d'une inode.\n");
			return 1;
		}
		r5Disk.inodes[i] = strtoind(buffer);
	}
	return 0;
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

uchar *sbtostr(super_block_t sb) {
	/// \brief Transforme la structure super_block_t en chaine de caractères
	/// \return la chaine de caractères
	unsigned char *str = malloc(sizeof(super_block_t) * sizeof(unsigned char));
	memcpy(str, &sb.raid_type, sizeof(sb.raid_type));
	int i = (int)sizeof(sb.raid_type);
	memcpy(&str[i], &sb.nb_blocks_used, sizeof(uint));
	i += (int)sizeof(uint);
	memcpy(&str[i], &sb.first_free_byte, sizeof(uint));
	return str;
}

int write_super_block(int *startbyte) {
    uchar *buffer = sbtostr(r5Disk.super_block);
    if((*startbyte = write_chunk(buffer, sizeof(super_block_t), 0)) == -1) {
        fprintf(stderr, "Erreur lors de l'ecriture du super block.\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

super_block_t strtosb(uchar *str) {
	super_block_t sb;
	memcpy(&sb.raid_type, str, sizeof(sb.raid_type));
	int i = (int)sizeof(sb.raid_type);
	memcpy(&sb.nb_blocks_used, &str[i], sizeof(uint));
	i += (int)sizeof(uint);
	memcpy(&sb.first_free_byte, &str[i], sizeof(uint));
	return sb;
}

int read_super_block() {
	uchar *buffer = malloc(sizeof(uchar) * sizeof(super_block_t));
	if(read_chunk(buffer, sizeof(super_block_t), 0) == -1) {
		fprintf(stderr, "Erreur lors de la lecture du super block.\n");
        return EXIT_FAILURE;
	}
	r5Disk.super_block = strtosb(buffer);
	return EXIT_SUCCESS;
}

inode_t init_inode(char *filename, uint size, uint position) {
	inode_t inode;
	strcpy(inode.filename, filename);
	inode.size = size;
	inode.first_byte = position;
	inode.nblock = 0;
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

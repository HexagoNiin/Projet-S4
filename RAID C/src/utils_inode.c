#include "../headers/utils_inode.h"

void delete_inode(int pos){
	/**
    * \brief Supprime un noeud sur la table des index.
    * \param[in] pos : position du noeud à supprimer.
    */

	/* mise a jour super_block */
	r5Disk.super_block.nb_blocks_used -= r5Disk.inodes[pos].nblock;
	if(pos == INODE_TABLE_SIZE - 1 && !r5Disk.inodes[pos+1].first_byte)
		r5Disk.super_block.first_free_byte -= (r5Disk.inodes[pos].nblock / r5Disk.ndisk) * BLOCK_SIZE;

	/* supprime l'inode */
	r5Disk.inodes[pos].first_byte = 0;
	strcpy(r5Disk.inodes[pos].filename, "");

	/* regroupe les inodes */
	int i;
	for(i=pos; i < INODE_TABLE_SIZE-1; i++)
		r5Disk.inodes[i] = r5Disk.inodes[i+1];
	r5Disk.number_of_files--;
	write_inodes_table((SUPER_BLOCK_SIZE / r5Disk.ndisk) * BLOCK_SIZE);
	write_super_block();
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
    /// \param[in] startbyte : position en octet
    /// \return -1 s'il y a eu une erreur, le nombre de bandes écrites sinon
    int i, nStripe = 0;
	int totalStripe = 0;
	uchar *buffer = NULL;
    for(i=0;i<INODE_TABLE_SIZE;i++) {
        buffer = indtostr(r5Disk.inodes[i]);
		log3("[WRITE_INODES_TABLE] Ecriture inode num %d", i);
		nStripe = write_chunk(buffer, sizeof(inode_t), startbyte + (i * nStripe * BLOCK_SIZE));
        if(nStripe == -1) {
            return -1;
        }
		totalStripe += nStripe;
		free(buffer);
    }
	log3("[WRITE_INODES_TABLE] totalStripe : %d", totalStripe)
    return totalStripe;
}

inode_t strtoind(uchar *str) {
	/// \brief Transforme une chaine de caractères en inode.
	/// \param[in] str : chaine de caractères
	/// \return l'inode générée
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
	/// \brief Remplie la table d'inodes à partir du système RAID
	/// \param[in] startbyte : position où se situe la table sur le RAID
	/// \return 0 s'il a eu une erreur, 1 sinon
	int i, nStripe = 0;
	uchar *buffer = malloc(sizeof(uchar) * sizeof(inode_t));
	for(i=0;i<INODE_TABLE_SIZE;i++) {
		nStripe = read_chunk(buffer, sizeof(inode_t), startbyte + (i * nStripe * BLOCK_SIZE));
		if(nStripe == -1) {
			free(buffer);
			return EXIT_FAILURE;
		}
		r5Disk.inodes[i] = strtoind(buffer);
	}
	free(buffer);
	return EXIT_SUCCESS;
}

int get_unused_inode() {
    /// \brief Retourne l'indice du premier inode disponible dans la table.
    /// \return L'indice d'un inode ou -1 si la table est pleine
    int i;
	log3("[GET_UNUSED_INODE] Parcours de la table d'inode :");
    for(i=0;i<INODE_TABLE_SIZE;i++) {
		log3("[GET_UNUSED_INODE] [%d] first_byte : %d", i, r5Disk.inodes[i].first_byte);
        if(r5Disk.inodes[i].first_byte == 0)
            return i;
    }
    return -1;
}

uchar *sbtostr(super_block_t sb) {
	/// \brief Transforme la structure super_block_t en chaine de caractères
	/// \return la chaine de caractères
	uchar *str = malloc(sizeof(super_block_t) * sizeof(uchar));
	memcpy(str, &sb.raid_type, sizeof(sb.raid_type));
	int i = (int)sizeof(sb.raid_type);
	memcpy(&str[i], &sb.nb_blocks_used, sizeof(uint));
	i += (int)sizeof(uint);
	memcpy(&str[i], &sb.first_free_byte, sizeof(uint));

	return str;
}

int write_super_block() {
	/// \brief Ecrit le super block sur le système RAID
	/// \param[out] startbyte : premiere bande libre sur le RAID
	/// \return 0 s'il y a une erreur, 1 sinon
    uchar *buffer = sbtostr(r5Disk.super_block);
	int code_retour = write_chunk(buffer, sizeof(super_block_t), 0);
    if(code_retour == -1) {
		log3("[WRITE_SUPER_BLOCK] Erreur ecriture du chunk");
        return EXIT_FAILURE;
    }
	free(buffer);
    return EXIT_SUCCESS;
}

super_block_t strtosb(uchar *str) {
	/// \brief Transforme une chaine de caractères en super block
	/// \param[in] str : la chaine de caractères
	/// \return le super block généré

	super_block_t sb;
	memcpy(&sb.raid_type, str, sizeof(sb.raid_type));
	int i = (int)sizeof(sb.raid_type);
	memcpy(&sb.nb_blocks_used, &str[i], sizeof(uint));
	i += (int)sizeof(uint);
	memcpy(&sb.first_free_byte, &str[i], sizeof(uint));
	return sb;
}

int read_super_block() {
	/// \brief Génère le super block à partir du RAID
	/// \return 0 s'il y a eu une erreur, 1 sinon
	uchar *buffer = malloc(sizeof(uchar) * sizeof(super_block_t));
	int code_retour;
		if(r5Disk.raidmode == ZERO)
			code_retour = read_chunk_raid0(buffer, sizeof(super_block_t), 0);
		else if(r5Disk.raidmode == UN)
			code_retour = read_chunk_raid1(buffer, sizeof(super_block_t), 0);
		else if(r5Disk.raidmode == CINQUANTE)
			code_retour = read_chunk_raid50(buffer, sizeof(super_block_t), 0);
		else
			code_retour = read_chunk_raid5(buffer, sizeof(super_block_t), 0);
	if(code_retour == -1)
        return EXIT_FAILURE;
	r5Disk.super_block = strtosb(buffer);
	free(buffer);
	return EXIT_SUCCESS;
}

inode_t init_inode(const char *filename, uint size, uint position) {
	/// \brief Initialise une inode selon des informations de fichier
	/// \param[in] filename : le nom du fichier
	/// \param[in] size : la taille du fichier en octets
	/// \param[in] position : la positon du fichier sur le RAID
	/// \return l'inode créée
	log3("[UPDATE_INODES_TABLE] Creation inode : nom %s taille %d position %d", filename, size, position);
	inode_t inode;
	strcpy(inode.filename, filename);
	inode.size = size;
	inode.first_byte = position;
	inode.nblock = 0;
	return inode;
}

int update_inodes_table(inode_t inode) {
	/// \brief Met à jour la table d'inode
	/// \param[in] inode ; l'inode qui a été ajoutée à la table d'inodes
	/// \return 0 s'il y a eu une erreur, 1 sinon
	if(r5Disk.number_of_files < INODE_TABLE_SIZE) {
		r5Disk.inodes[get_unused_inode()] = inode;
		log3("[UPDATE_INODES_TABLE] Prochaine inode libre : %d", get_unused_inode());

		r5Disk.number_of_files++;
		update_first_free_byte((inode.nblock / r5Disk.ndisk) * BLOCK_SIZE);
		r5Disk.super_block.nb_blocks_used += inode.nblock;
		return EXIT_SUCCESS;
	} else {
		fprintf(stderr, "Erreur, la table d'inodes est pleine, le fichier n'a pas ete ajoute.\n");
		return EXIT_FAILURE;
	}
}

void update_first_free_byte(int new_byte) {
	/// \brief Met à jour le premier octet libre sur le super bloc
	/// \param[in] new_byte : nombre d'octets à ajouter
	r5Disk.super_block.first_free_byte += new_byte;
}

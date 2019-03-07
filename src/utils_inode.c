#include "../headers/utils_inode.h"

int write_inodes_table(inode_t inode, int pos, FILE **files) {
    uchar buffer[MAX_MSG];
    int i;
    strcpy((char*)buffer, inode.filename);
    i = FILENAME_MAX_SIZE;
    if((i += sprintf((char*)&buffer[i], "%d", inode.size)) < 0) {
        fprintf(stderr, "Il y a eu un probleme lors de l'ecriture dans la chaine de carcteres.\n");
        return EXIT_FAILURE; //1
    }

    if((i += sprintf((char*)&buffer[i], "%d", inode.nblock)) < 0) {
        fprintf(stderr, "Il y a eu un probleme lors de l'ecriture dans la chaine de carcteres.\n");
        return EXIT_FAILURE; //1
    }

    if((i += sprintf((char*)&buffer[i], "%d", inode.first_byte)) < 0) {
        fprintf(stderr, "Il y a eu un probleme lors de l'ecriture dans la chaine de carcteres.\n");
        return EXIT_FAILURE; //1
    }
    write_chunk(buffer, i, pos, files);
    return EXIT_SUCCESS;
}

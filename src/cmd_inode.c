#include "../headers/utils_inode.h"

void dump_inode(inode_t inode) {
    printf("Inode :\n\tNom du fichier : %s\n", inode.filename);
    printf("\tTaille en octets : %d\n", inode.size);
    printf("\tPosition sur le systeme : %d\n", inode.first_byte);
    printf("\tNombre de blocks : %d\n", inode.nblock);
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage : <%d> nom_repertoire\n", argv[0]);
    }

    

}

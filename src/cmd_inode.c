#include <sys/types.h>
#include <dirent.h>
#include "../headers/utils_inode.h"

void dump_inode(inode_t inode) {
    if(inode.first_byte != 0) {
        printf("Inode :\n\tNom du fichier : %s\n", inode.filename);
        printf("\tTaille en octets : %d\n", inode.size);
        printf("\tPosition sur le systeme : %d\n", inode.first_byte);
        printf("\tNombre de blocks : %d\n", inode.nblock);
    } else {
        printf("Inode vide\n");
    }
}

int nFiles(DIR *dir) {
    int count = 0;
    while(readdir(dir) != NULL)
        count++;
    rewinddir(dir);
    return count;
}

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage : <%s> nom_repertoire\n", argv[0]);
    }

    DIR *dir = opendir(argv[1]);
    if(dir == NULL) {
        fprintf(stderr, "Une erreur est survenue lors de l'ouverture du dossier.\n");
        exit(1);
    }
    int count = nFiles(dir);
    FILE **raid = malloc(sizeof(FILE *) * count);
    struct dirent *f;
    int i = 0;
    while((f = readdir(dir)) != NULL) {
        raid[i] = fopen(f->d_name, "r");
        ++i;
    }
    closedir(dir);

    inode_table_t table;
    if(read_inodes_table(table, raid)) {
        fprintf(stderr, "Erreur lors de la lecture de la table.\n");
        exit(2);
    }

    for(i=0;i<INODE_TABLE_SIZE;i++) {
        dump_inode(table[i]);
    }

    for(i=0;i<count;i++)
        fclose(raid[i]);

    free(raid);

}

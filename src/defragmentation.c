#include "../headers/utils_inode.h"
#include "../headers/utils_virtual_disk.h"

int main(int argc, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage : <%s> repertory\n", argv[0]);
        return 1;
    }
    if(init_disk_raid5(argv[1]))
        return 2;

    if(r5Disk.super_block.nb_blocks_used == SUPER_BLOCK_SIZE) {
        fprintf(stderr, "Erreur, le systeme doit exister pour pouvoir le fragmenter.\n");
        return 3;
    }

    int i = 1;
    while(r5Disk.inodes[i].first_byte && i < INODE_TABLE_SIZE) {
        if(r5Disk.inodes[i].first_byte != (r5Disk.inodes[i-1].first_byte + r5Disk.inodes[i-1].nblock)) {
            uchar *str = malloc(r5Disk.inodes[i].size * sizeof(uchar));
            if(read_chunk(str, r5Disk.inodes[i].size, r5Disk.inodes[i].first_byte) == -1) {
                printf("Erreur lecture.\n");
            }
            r5Disk.inodes[i].first_byte = r5Disk.inodes[i-1].first_byte + r5Disk.inodes[i-1].nblock;
            if(write_chunk(str, r5Disk.inodes[i].size, r5Disk.inodes[i].first_byte) == -1) {
                printf("Erreur ecriture.\n");
            }
            free(str);
        }
        i++;
    }

    int u;
    printf("Affichage de la table d'inodes :\n");
    for(u=0;u<INODE_TABLE_SIZE;u++) {
        printf("Inodes %d : taille %d pos %d nblock %d\n", u, r5Disk.inodes[u].size, r5Disk.inodes[u].first_byte, r5Disk.inodes[u].nblock);
    }

}

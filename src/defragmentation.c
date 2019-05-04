#include "../headers/inode.h"
#include "../Headers/utils_virtual_disk.h"

int main(int argv, char *argv[]) {
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
        printf("%d %d\n", r5Disk.inodes[i].first_byte, r5Disk.inodes[i-1].first_byte + r5Disk.inodes[i-1] * BLOCK_SIZE);
        if(r5Disk.inodes[i].first_byte != (r5Disk.inodes[i-1].first_byte + r5Disk.inodes[i-1] * BLOCK_SIZE)) {
            /*
            uchar *str = malloc(sizeof(r5Disk.inodes[i].size) * sizeof(uchar));
            read_chunk(str, r5Disk.inodes[i].size, r5Disk.inodes[i].first_byte);

            free(str);
            */
        }
        i++;
    }

}

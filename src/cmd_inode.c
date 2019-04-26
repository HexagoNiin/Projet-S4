#include <sys/types.h>
#include <dirent.h>
#include "../headers/utils_inode.h"
#include "../headers/utils_virtual_disk.h"

void dump_inode(inode_t inode) {
    if(inode.first_byte != 0) {
        printf("Inode :\n\tNom du fichier : %s\n", inode.filename);
        printf("\tTaille en octets : %d\n", inode.size);
        printf("\tPosition sur le systeme : %d\n", inode.first_byte);
        printf("\tNombre de blocks : %d\n\n", inode.nblock);
    } else {
        printf("Inode vide\n\n");
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
		exit(1);
    }

    init_disk_raid5(argv[1]);
    int startbyte;
    write_super_block(&startbyte);
    startbyte *= BLOCK_SIZE;
    int valeur_random = 33;
    printf("[CREATE] :\n\n");
    update_inodes_table(init_inode("oiseau.png", 64, valeur_random));
    dump_inode(r5Disk.inodes[0]);
    update_inodes_table(init_inode("doggos.txt", 32, valeur_random));
    dump_inode(r5Disk.inodes[1]);
    update_inodes_table(init_inode("satan.mp33", 64, valeur_random));
    dump_inode(r5Disk.inodes[2]);
    write_inodes_table(startbyte);
    printf("[DELETE] :\n\n");
    delete_inode(0);
    delete_inode(0);
    delete_inode(0);
    dump_inode(r5Disk.inodes[0]);
    dump_inode(r5Disk.inodes[1]);
    dump_inode(r5Disk.inodes[2]);
    printf("[READ] :\n\n");
    read_inodes_table(startbyte);
    int i;
    for(i=0;i<INODE_TABLE_SIZE;i++) {
        dump_inode(r5Disk.inodes[i]);
    }

}

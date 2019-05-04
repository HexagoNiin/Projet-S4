#include "../headers/inode.h"
#include "../Headers/utils_virtual_disk.h"

int main(int argv, char *argv[]) {
    if(argc != 2) {
        fprintf(stderr, "Usage : <%s> repertory\n", argv[0]);
        return 1;
    }
    init_disk_raid5(argv[1]);
}

#include "../headers/utils_os.h"

int main(int argc, char *argv[]) {
	log1("[MAIN] Logs de niveau 1 activés");
	log2("[MAIN] Logs de niveau 2 activés");
	log3("[MAIN] Logs de niveau 3 activés");
	log4("[MAIN] Logs de niveau 4 activés");
	log5("[MAIN] Logs de niveau 5 activés");
	log6("[MAIN] Logs de niveau 6 activés");
    if(argc != 2) {
        fprintf(stderr, "Usage : <%s> repertory\n", argv[0]);
        exit(1);
    }
	init_disk_raid5(argv[1]);
    log1("[R5DISK] nfiles %d", r5Disk.number_of_files);
    log1("      SP block used %d", r5Disk.super_block.nb_blocks_used);
    log1("      SP free byte  %d", r5Disk.super_block.first_free_byte);
    log1("         ndisk %d", r5Disk.ndisk);
    interpreteur();
    close_system();
    return 0;
}

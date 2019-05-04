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
        return 1;
    }
	if(init_disk_raid5(argv[1]))
		return 1;
    interpreteur();
    close_system();
    return 0;
}

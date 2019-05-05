#include "../headers/utils_os.h"

int check_raid_exists(char *raid, char raid_type[NB_RAIDS][32]) {
	int i;
	for(i=0;i<NB_RAIDS;i++) {
		if(!strcmp(raid, raid_type[i]))
			return i+1;
	}
	return 0;
}


int main(int argc, char *argv[]) {
	log1("[MAIN] Logs de niveau 1 activés");
	log2("[MAIN] Logs de niveau 2 activés");
	log3("[MAIN] Logs de niveau 3 activés");
	log4("[MAIN] Logs de niveau 4 activés");
	log5("[MAIN] Logs de niveau 5 activés");
	log6("[MAIN] Logs de niveau 6 activés");
    if(argc < 2) {
        fprintf(stderr, "Usage : <%s> repertory type_raid\n", argv[0]);
        return 1;
    }
	char raid_type[NB_RAIDS][32] = {"zero", "un", "cinq", "zero_un", "un_zero", "cinquante", "cent"};
	int raid;
	if(argc == 2) {
		raid = 2;
	} else {
		raid = check_raid_exists(argv[2], raid_type);
	}
	if(!raid) {
		fprintf(stderr, "Les types de raids sont : zero, un, cinq, zero_un, un_zero, cinquante, cent\n");
		return 2;
	}

	if(init_disk_raid5(argv[1], raid))
		return 1;
    interpreteur();
    close_system();
    return 0;
}

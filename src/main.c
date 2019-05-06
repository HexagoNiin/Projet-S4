#include "../headers/utils_os.h"

int check_raid_exists(char *raid, char raid_type[NB_RAIDS][32]) {
	int i;
	for(i=0;i<NB_RAIDS;i++) {
		if(!strcmp(raid, raid_type[i]))
			return i+1;
	}
	return 0;
}

bool get_grappes(char *grappe, enum raid raid) {
	if(raid == CINQUANTE && (strlen(grappe) != 3 || grappe[1] != ':' || grappe[0] - 48 < 2 || grappe[0] - 48 > 9 || grappe[2] - 48 < 3 || grappe[2] - 48 > 9)) {
		fprintf(stderr, "Le nombre de grappe doit etre compris entre 2 et 9 compris et la taille des grappes doit etre comprise entre 3 et 9 compris.\nLe format a respecter est le suivant : ngrappe:sgrappe\n");
		return false;
	}

	if(raid == ZERO_UN && (strlen(grappe) != 3 || grappe[1] != ':' || grappe[0] - 48 < 2 || grappe[0] - 48 > 9 || grappe[2] - 48 < 2 || grappe[2] - 48 > 9)) {
		fprintf(stderr, "Le nombre de grappe doit etre compris entre 2 et 9 compris et la taille des grappes doit etre comprise entre 2 et 9 compris.\nLe format a respecter est le suivant : ngrappe:sgrappe\n");
		return false;
	}
	r5Disk.nb_grappe = grappe[0] - 48;
	r5Disk.size_grappe = grappe[2] - 48;
	return true;
}

int main(int argc, char *argv[]) {
	log1("[MAIN] Logs de niveau 1 activés");
	log2("[MAIN] Logs de niveau 2 activés");
	log3("[MAIN] Logs de niveau 3 activés");
	log4("[MAIN] Logs de niveau 4 activés");
	log5("[MAIN] Logs de niveau 5 activés");
	log6("[MAIN] Logs de niveau 6 activés");
    if(argc < 2) {
        fprintf(stderr, "Usage : <%s> repertory [type_raid [ngrappe:sgrappe]]\n", argv[0]);
        return 1;
    }
	char raid_type[NB_RAIDS][32] = {"zero", "un", "cinq", "zero_un", "un_zero", "cinquante", "cent"};
	int raid;
	if(argc == 2) {
		log1("[MAIN] Mode par défaut : cinq");
		raid = 3;
	} else {
		raid = check_raid_exists(argv[2], raid_type);
		log1("[MAIN] Mode sélectionné : %s", raid_type[raid-1]);
	}
	if(!raid) {
		fprintf(stderr, "Les types de raids sont : zero, un, cinq, zero_un, un_zero, cinquante, cent\n");
		return 2;
	}
	if(raid == CINQUANTE || raid == ZERO_UN) {
		if(argc != 4) {
			fprintf(stderr, "Pour le raid composes la commande s'utilise comme suit :\n");
			fprintf(stderr, "<%s> repertory raid nombre_de_grappes:taille_de_grappe\n", argv[0]);
			return 3;
		}
		if(!get_grappes(argv[3], raid))
			return 4;
	}

	//faire en sorte que le systeme ait acces aux grappes pour le raid 50
	if(init_disk_raid5(argv[1], raid))
		return 1;
    interpreteur();
    close_system();
    return 0;
}

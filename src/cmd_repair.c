#include "../headers/utils_os.h"

int main(int argc, char *argv[]) {
	if(argc != 3) {
		fprintf(stderr, "Usage : <%s> repertory disk_id", argv[0]);
		return 1;
	}
	int indice = atoi(argv[2]);
	if(indice < 0 || indice > 10) {
		fprintf(stderr, "L'indice du repertoire doit etre compris entre 0 et 10.\n");
		return 2;
	}

	DIR *rep;
	if(!(rep = opendir(argv[1]))) {
		fprintf(stderr, "Erreur lors de l'ouverture du repertoire.\n");
		return 3;
	}

	int nbFiles = 0;
	struct dirent *disk;
	while((disk = readdir(rep))) {
		if(strcmp(disk->d_name, ".") && strcmp(disk->d_name, ".."))
			nbFiles++;
	}
	nbFiles++;
	rewinddir(rep);

	FILE **storage = malloc(sizeof(FILE *) * nbFiles);
	int i = 0;
	while((disk = readdir(rep))) {
		if(strcmp(disk->d_name, ".") && strcmp(disk->d_name, "..")) {
			char chemin[512];
			if(indice == i) {
				sprintf(chemin, "%s/d%d", argv[1], indice);
				if(!(storage[indice] = fopen(chemin, "w"))) {
					fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", disk->d_name);
					return 4;
				}
				i++;
			}
			sprintf(chemin, "%s/%s", argv[1], disk->d_name);
			if(!(storage[i] = fopen(chemin, "r"))) {
				fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", disk->d_name);
				return 4;
			}
			i++;
		}
	}
	closedir(rep);
	r5Disk.ndisk = nbFiles;
	r5Disk.storage = storage;
	repair_disk(indice);
}

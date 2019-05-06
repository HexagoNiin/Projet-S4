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
	rewinddir(rep);

	FILE **storage = malloc(sizeof(FILE *) * nbFiles);
	int i = nbFiles-1;
	while((disk = readdir(rep))) {
		if(strcmp(disk->d_name, ".") && strcmp(disk->d_name, "..")) {
			char chemin[512];
			int len = strlen(disk->d_name);
			printf("name%d ind%d i%d\n",disk->d_name[len-1]-48, indice, i);
			if(disk->d_name[len-1]-48 == indice) {
				sprintf(chemin, "%s/%s", argv[1], disk->d_name);
				if(!(storage[indice] = fopen(chemin, "w"))) {
					fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", disk->d_name);
					return 4;
				}
			} else {
				sprintf(chemin, "%s/%s", argv[1], disk->d_name);
				printf("i : %d\n", i);
				if(!(storage[i] = fopen(chemin, "r"))) {
					fprintf(stderr, "Erreur lors de l'ouverture du fichier %s.\n", disk->d_name);
					return 4;
				}
			}
			i--;
		}
	}
	closedir(rep);
	r5Disk.ndisk = nbFiles;
	r5Disk.storage = storage;
	repair_disk(indice);
}

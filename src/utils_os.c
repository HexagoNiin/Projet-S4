#include "../headers/utils_os.h"

char command_list[NB_COMMANDS][COMMANDS_SIZE] = {"ls", "cat", "rm", "create", "edit", "load", "store"};
FunctionStr command_exec[NB_COMMANDS] = {&ls, &cat, &rm, &create, &edit, &load, &store};

void interpreteur(char *workspace) {
	log1("[INTERPRETEUR] Lancement interpreteur\n");
    char *command = malloc(sizeof(char) * (COMMANDS_SIZE + FILENAME_MAX_SIZE + 2));
    char **command_option = NULL;
    int exit = 0;

    while(exit != -2) {
        printf("\x1B[94mSysteme RAID\x1B[0m$ ");
        fgets(command, COMMANDS_SIZE + FILENAME_MAX_SIZE + 2, stdin);
        command_option = parser(command);
        if(command_option) {
            exit = action(command_option, workspace);
			if(exit) {log1("Erreur lors de l'exécution de la commande\nCode de retour : %d", exit);}
			log1(" ");
		}
        else
            fprintf(stderr, "\x1B[91m[ERR]\x1B[0m Usage : command [option]\n");
    }
}

int action(char **command, char *workspace) {
    /// \brief execute l'action d'une command + option passé en paramètre
    /// \command command + option
    /// \return -1 si la commande est invalide, -2 si l'on veut quitter le shell, le code de retour de la commande executee sinon
    int i;
    for(i=0;i<NB_COMMANDS;i++) {
        if(!strcmp(command[0], command_list[i])) {
			log1("[INTERPRETEUR] Exécution de %s", command[0])
            return command_exec[i](command[1], workspace);
        }
    }
    if(strcmp(command[0], "quit")) {
        fprintf(stderr, "\x1B[91m[ERR]\x1B[0m La commande rentree est invalide.\n");
        return -1;
    }
    return -2;
}

int ls(char *option, char *workspace) {
	DIR *directory;
	if((directory = opendir(workspace))) {
		fprintf(stderr, ROUGE "[ERR]" BLANC "Le nom du repertoire n'est valide.\n");
		return -1;
	}
	struct dirent *fichier;
	struct stat infos;
	while((fichier = readdir(directory))) {
		if(strcmp(fichier->d_name, ".") && strcmp(fichier->d_name, "..")) {
			if(!stat(fichier->d_name, &infos)) {
				fprintf(stderr, ROUGE "[ERR]" BLANC "La recuperation des informations du fichier n'a pas aboutie.\n");
				return -2;
			}
			if(!strcmp(option, "-l")) {
				printf("%d", (int)infos.st_nlink);
				printf(" %d", (int)infos.st_uid);
				printf(" %d", (int)infos.st_gid);
				printf(" %d", (int)infos.st_size);
				printf(" %s", ctime(infos.st_atime));
				printf(" %s", fichier->d_name);
			} else {
				printf("%s", fichier->d_name);
			} printf("\n");
		}
	}
	return 0;
}

int cat(char *filename, char *workspace) {
	(void)workspace;
    file_t file;
	read_file(filename, &file);
	printf("%s", file.data);
    return 0;
}

int rm(char *filename, char *workspace) {
    (void)filename;
    return 0;
}

int create(char *filename, char *workspace) {
    (void)filename;
    return 0;
}

int edit(char *filename, char *workspace) {
    (void)filename;
    return 0;
}

int load(char *arguments, char *workspace) {
    return load_file_from_host(arguments);
}

int store(char *filename, char *workspace) {
    return store_file_to_host(filename);
}

char **parser(char *command) {
    /// \brief Analyse la chaine de caractères et la transfome en command + option
    /// \param[in] command : la chaine de caractères à analyser
    /// \return NULL s'il y a eu une erreur ou le tableau command + option sinon
    char **command_option = malloc(sizeof(char*) * (NB_OPTIONS + 1));
    int u;
    for(u=0;u<NB_OPTIONS+1;u++)
        command_option[u] = malloc(sizeof(char) * FILENAME_MAX_SIZE);

    char *token;
    token = strtok(command, " \n");
    int i = 0;
    while(token != NULL) {
        if(i > NB_OPTIONS)
            return NULL;
        strcpy(command_option[i], token);
        token = strtok(NULL, " \n");
        i++;
    }
    return command_option;
}

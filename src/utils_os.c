#include "../headers/utils_os.h"

char command_list[NB_COMMANDS][COMMANDS_SIZE] = {"ls", "cat", "rm", "create", "edit", "load", "store"};
FunctionStr command_exec[NB_COMMANDS] = {&ls, &cat, &rm, &create, &edit, &load, &store};

void interpreteur() {
	log1("[INTERPRETEUR] Lancement interpreteur\n");
    char *command = malloc(sizeof(char) * (COMMANDS_SIZE + FILENAME_MAX_SIZE + 2));
    char **command_option = NULL;
    int exit = 0;

    while(exit != -2) {
        printf("\x1B[94mSysteme RAID\x1B[0m$ ");
        fgets(command, COMMANDS_SIZE + FILENAME_MAX_SIZE + 2, stdin);
        command_option = parser(command);
        if(command_option) {
            exit = action(command_option);
			if(exit) {log1("Erreur lors de l'exécution de la commande\nCode de retour : %d", exit);}
			log1(" ");
		}
        else
            fprintf(stderr, "\x1B[91m[ERR]\x1B[0m Usage : command [option]\n");
    }
}

int action(char **command) {
    /// \brief execute l'action d'une command + option passé en paramètre
    /// \command command + option
    /// \return -1 si la commande est invalide, -2 si l'on veut quitter le shell, le code de retour de la commande executee sinon
    int i;
    for(i=0;i<NB_COMMANDS;i++) {
        if(!strcmp(command[0], command_list[i])) {
<<<<<<< HEAD
			log1("[INTERPRETEUR] Exécution de %s", command[0])
            return command_exec[i](command[1]);
=======
			log1("[INTERPRETEUR] Exécution de %s", command[0]);
            return command_exec[i](command[1], workspace);
>>>>>>> 04250de60fdcb4e5280e1e2022db9f6fae7ecb85
        }
    }
    if(strcmp(command[0], "quit")) {
        fprintf(stderr, "\x1B[91m[ERR]\x1B[0m La commande rentree est invalide.\n");
        return -1;
    }
    return -2;
}

int ls(char *option) {
	return 0;
}

int cat(char *filename) {
    file_t file;
	read_file(filename, &file);
	printf("%s", file.data);
    return 0;
}

<<<<<<< HEAD
int rm(char *filename) {
    (void)filename;
=======
int rm(char *filename, char *workspace) {
    int i = 0;
	log1("[RM] Parcours de la table d'inodes : (%d emplacements)", INODE_TABLE_SIZE);
	while(i < INODE_TABLE_SIZE && strcmp(r5Disk.inodes[i].filename, "") && strcmp(r5Disk.inodes[i].filename, filename)) {
		log1("[RM] [%2d] %s", i, r5Disk.inodes[i].filename);
		i++;
	}
	log1("[RM] [%2d] %s", i, r5Disk.inodes[i].filename);
	if(strcmp(r5Disk.inodes[i].filename, filename)) {
		fprintf(stderr, "\x1B[91m[ERR]\x1B[0m Le fichier n'a pas été trouvé.\n");
		return 1;
	}
	log1("[RM] Suppression de l'entrée %d", i);
	delete_inode(i);
>>>>>>> 04250de60fdcb4e5280e1e2022db9f6fae7ecb85
    return 0;
}

int create(char *filename) {
    (void)filename;
    return 0;
}

int edit(char *filename) {
    (void)filename;
    return 0;
}

int load(char *arguments) {
    return load_file_from_host(arguments);
}

int store(char *filename) {
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

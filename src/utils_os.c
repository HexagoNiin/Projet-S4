#include "../headers/utils_os.h"

char command_list[NB_COMMANDS][COMMANDS_SIZE] = {"ls", "cat", "rm", "create", "edit", "load", "store"};
FunctionStr command_exec[NB_COMMANDS] = {&ls, &cat, &rm, &create, &edit, &load, &store};

void interpreteur() {
    char *command = malloc(sizeof(char) * (COMMANDS_SIZE + FILENAME_MAX_SIZE + 2));
    char **command_option = NULL;
    int exit = 0;

    while(exit != -2) {
        printf("\x1B[94mSysteme RAID\x1B[0m$ ");
        fgets(command, COMMANDS_SIZE + FILENAME_MAX_SIZE + 2, stdin);
        command_option = parser(command);
        if(command_option)
            exit = action(command_option);
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
            return command_exec[i]((command[1]));
        }
    }
    if(strcmp(command[0], "quit")) {
        fprintf(stderr, "\x1B[91m[ERR]\x1B[0m La commande rentree est invalide.\n");
        return -1;
    }
    return -2;
}

int ls(char *option) {
    (void)option;
    return 0;
}

int cat(char *filename) {
    (void)filename;
    return 0;
}

int rm(char *filename) {
    (void)filename;
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

int load(char *filename) {
    (void)filename;
    return 0;
}

int store(char *filename) {
    (void)filename;
    return 0;
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

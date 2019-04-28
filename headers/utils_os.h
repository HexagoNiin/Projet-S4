#ifndef _UTILS_OS
#define _UTILS_OS

#include "utils_file.h"
#include <time.h>
#include "couleur.h"

#define NB_COMMANDS 7
#define COMMANDS_SIZE 16
#define NB_OPTIONS 1

typedef int(*FunctionStr)(char*, char*);

int action(char **command, char *workspace);
int cat(char *filename, char *workspace);
int ls(char *option, char *workspace);
int rm(char *filename, char *workspace);
int create(char *filename, char *workspace);
int edit(char *filename, char *workspace);
int load(char *arguments, char *workspace);
int store(char *filename, char *workspace);


void interpreteur(char *workspace);
char **parser(char *command);

#endif

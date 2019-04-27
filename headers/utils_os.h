#ifndef _UTILS_OS
#define _UTILS_OS

#include <string.h>
#include "utils_file.h"

#define NB_COMMANDS 7
#define COMMANDS_SIZE 16
#define NB_OPTIONS 1

typedef int(*FunctionStr)(char*);

int action(char **command);
int cat(char *filename);
int ls(char *option);
int rm(char *filename);
int create(char *filename);
int edit(char *filename);
int load(char *arguments);
int store(char *filename);


void interpreteur();
char **parser(char *command);

#endif

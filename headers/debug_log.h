#include "couleur.h"

#ifdef _DEBUG_LOG
#define debug(x, ...) printf("%s", ROUGE);printf(x, __VA_ARGS__);printf("%s\n", RESET)
#else
#define debug(x, ...)
#endif

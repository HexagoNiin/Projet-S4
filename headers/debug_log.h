/// \file debug_log.h
/// \brief Utilitaires permettant de créer des macros de debug
/// \author Ugo EB-LEVADOUX
/// \author Axel GAUTHIER
/// \author Cédric MARTIN
/// \date 2019

#include "couleur.h"

#define debug(...)\
	printf("%s", MAGENTA);\
	printf(__VA_ARGS__);\
	printf("%s\n", RESET);

#if defined _LOG6
#define log6(...) debug(__VA_ARGS__)
#else
#define log6(...)
#endif

#if defined _LOG5
#define log5(...) debug(__VA_ARGS__)
#else
#define log5(...) log6(__VA_ARGS__)
#endif

#if defined _LOG4
#define log4(...) debug(__VA_ARGS__)
#else
#define log4(...) log5(__VA_ARGS__)
#endif

#if defined _LOG3
#define log3(...) debug(__VA_ARGS__)
#else
#define log3(...) log4(__VA_ARGS__)
#endif

#if defined _LOG2
#define log2(...) debug(__VA_ARGS__)
#else
#define log2(...) log3(__VA_ARGS__)
#endif

#if defined _LOG1
#define log1(...) debug(__VA_ARGS__)
#else
#define log1(...) log2(__VA_ARGS__)
#endif

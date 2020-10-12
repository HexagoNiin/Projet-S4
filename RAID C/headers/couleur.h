/// \file couleur.h
/// \brief Utilitaires permettant l'affichage coloré dans le terminal
/// \author Cédric MARTIN
/// \date 2018
#ifndef FORMATAGE
#define FORMATAGE

#define NOIR "\x1b[30m"
/// \def NOIR
///Le texte suivant sera écrit en noir s'il doit être écrit dans le terminal, normalement sinon
/// \def NOIR
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define ROUGE "\x1b[91m"
/// \def ROUGE
///Le texte suivant sera écrit en rouge s'il doit être écrit dans le terminal, normalement sinon
/// \def ROUGE
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define VERT "\x1b[92m"
/// \def VERT
///Le texte suivant sera écrit en vert s'il doit être écrit dans le terminal, normalement sinon
/// \def VERT
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define JAUNE "\x1b[93m"
/// \def JAUNE
///Le texte suivant sera écrit en jaune s'il doit être écrit dans le terminal, normalement sinon
/// \def JAUNE
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define BLEU "\x1b[94m"
/// \def BLEU
///Le texte suivant sera écrit en bleu s'il doit être écrit dans le terminal, normalement sinon
/// \def BLEU
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define MAGENTA "\x1b[95m"
/// \def MAGENTA
///Le texte suivant sera écrit en magenta s'il doit être écrit dans le terminal, normalement sinon
/// \def MAGENTA
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define CYAN "\x1b[96m"
/// \def CYAN
///Le texte suivant sera écrit en cyan s'il doit être écrit dans le terminal, normalement sinon
/// \def CYAN
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define BLANC "\x1b[97m"
/// \def BLANC
///Le texte suivant sera écrit en blanc s'il doit être écrit dans le terminal, normalement sinon
/// \def BLANC
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define NOIR2 "\x1b[90m"
/// \def NOIR2
///Le texte suivant sera écrit en gris foncé s'il doit être écrit dans le terminal, normalement sinon
/// \def NOIR2
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define ROUGE2 "\x1b[31m"
/// \def ROUGE2
///Le texte suivant sera écrit en rouge désaturé s'il doit être écrit dans le terminal, normalement sinon
/// \def ROUGE2
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define VERT2 "\x1b[32m"
/// \def VERT2
///Le texte suivant sera écrit en vert foncé s'il doit être écrit dans le terminal, normalement sinon
/// \def VERT2
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define JAUNE2 "\x1b[33m"
/// \def JAUNE2
///Le texte suivant sera écrit en ocre s'il doit être écrit dans le terminal, normalement sinon
/// \def JAUNE2
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define BLEU2 "\x1b[34m"
/// \def BLEU2
///Le texte suivant sera écrit en bleu désaturé s'il doit être écrit dans le terminal, normalement sinon
/// \def BLEU2
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define MAGENTA2 "\x1b[35m"
/// \def MAGENTA2
///Le texte suivant sera écrit en violet foncé s'il doit être écrit dans le terminal, normalement sinon
/// \def MAGENTA2
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define CYAN2 "\x1b[36m"
/// \def CYAN2
///Le texte suivant sera écrit en bleu ciel s'il doit être écrit dans le terminal, normalement sinon
/// \def CYAN2
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit
#define BLANC2 "\x1b[37m"
/// \def BLANC2
///Le texte suivant sera écrit en gris clair s'il doit être écrit dans le terminal, normalement sinon
/// \def BLANC2
///https://en.wikipedia.org/wiki/ANSI_escape_code#3/4_bit

#define SOULIGNE "\x1b[4m"
/// \def SOULIGNE
///Le texte suivant sera souligné s'il doit être écrit dans le terminal, normal sinon
/// \def SOULIGNE
///https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters
#define NSOULIGNE "\x1b[24m"
/// \def NSOULIGNE
///Le texte suivant ne sera pas souligné
/// \def NSOULIGNE
///https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters

#define RESET "\x1b[0m"
/// \def RESET
///Le texte suivant sera écrit normalement
/// \def RESET
///https://en.wikipedia.org/wiki/ANSI_escape_code#SGR_(Select_Graphic_Rendition)_parameters

#endif

#include "../headers/utils_os.h"

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
	log1("[MAIN] Logs de niveau 1 activés");
	log2("[MAIN] Logs de niveau 2 activés");
	log3("[MAIN] Logs de niveau 3 activés");
	log4("[MAIN] Logs de niveau 4 activés");
	log5("[MAIN] Logs de niveau 5 activés");
	log6("[MAIN] Logs de niveau 6 activés");
	log1(" ");
    interpreteur();
    return 0;
}

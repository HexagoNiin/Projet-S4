#include "../headers/utils_os.h"

int main(int argc, char *argv[]) {
	init_disk_raid5("systeme");
	if(argc != 2) {
		return 1;
	}
	repair_disk(atoi(argv[1]));
}

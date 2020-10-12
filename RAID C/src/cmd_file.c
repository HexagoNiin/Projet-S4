#include "../headers/utils_file.h"
#include "../headers/utils_virtual_disk.h"

#define CHEMIN "test.txt"

virtual_disk_t r5Disk;

int main() {
	init_disk_raid5("systeme");
	load_file_from_host(CHEMIN);
	return 0;
}

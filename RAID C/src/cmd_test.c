#include <stdio.h>
#include <stdlib.h>
#include "../headers/utils_stripe.h"
#include "../headers/utils_virtual_disk.h"

virtual_disk_t r5Disk;

void afficher(uchar * buffer, uchar * ref) {
	printf("[");
	for(int i = 0; i < 256; i++) {
		if(buffer[i] != ref[i]) printf("\x1B[91m");
		else printf("\x1B[96m");
		printf("%3d", buffer[i]);
		if(i != 255) printf ("\x1B[0m, ");
	}
	printf("\x1B[0m]\n");
}

int main() {
	printf("\x1B[94mINITIALISATION RAID5\x1B[0m\n");
    if(init_disk_raid5("systeme")) {printf("\x1B[91mECHEC\x1B[0m\n"); exit(1);}
	printf("\x1B[96mSUCCES\x1B[0m\n\n");

	printf("\x1B[94mCRÉATION BUFFER\x1B[0m\n");
    uchar * buffer = malloc(256 * sizeof(uchar));
	uchar * ref = malloc(256 * sizeof(uchar));
    for(int i = 0; i < 256; i++) {
        buffer[i] = i;
		ref[i] = i;
    }
	afficher(buffer, ref);
	printf("\n");
	printf("\x1B[94mÉCRITURE\x1B[0m\n");
    if(write_chunk(buffer, 256, 0) == -1) {printf("\x1B[91mECHEC\x1B[0m\n"); exit(1);}
	printf("\x1B[96mSUCCES\x1B[0m\n\n");
	printf("\x1B[94mLECTURE\x1B[0m\n");
	if(read_chunk(buffer, 256, 0)) {printf("\x1B[91mECHEC\x1B[0m\n"); exit(1);}
	printf("\x1B[96mSUCCES\x1B[0m\n\n");
	printf("\x1B[94mVERIFICATION BUFFER LU\x1B[0m\n");
	afficher(buffer, ref);
	(void)r5Disk;
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "../headers/utils_stripe.h"
#include "../headers/utils_virtual_disk.h"

int main() {
    virtual_disk_t r5Disk;
    init_disk_raid5("../systeme");
    uchar * buffer = malloc(256 * sizeof(uchar));
    for(int i = 0; i < 256; i++) {
        //printf("%u\n", i);
        buffer[i] = i;
    }
    write_chunk(buffer, 256, 0);
    return 0;
}

#include "sd.h"
#include "rprintf.h"
#include "serial.h"
#include <string.h>
#include "fat.h"

#define SECTOR_SIZE 512
struct boot_sector *bs;
char bootSector[512]; // Allocate a global array to store boot sector
char fat_table[8*SECTOR_SIZE];
unsigned int root_sector;

int fatInit() {
    sd_readblock(0, bootSector, 1); // Read sector 0 from disk drive into bootSector array
    bs = bootSector; // Point boot_sector struct to the boot sector so we can read fields
    // Print out some of the elements of the BIOS information block using rprintf...
    esp_printf(putc, "boot signature: %i\nnumber of fat tables: %i\nnumber of sectors per fat: %i\nnumber of reserved sectors: %i\nnumber of hidden sectors: %i", bs->boot_signature, bs->num_fat_tables, bs->num_sectors_per_fat, bs->num_reserved_sectors, bs->num_hidden_sectors);
    // TODO: Validate the boot signature = 0xaa55
    if (bs->boot_signature != 0xaa55) {
        return 0;
    }
    // TODO: Validate fs_type = "FAT12" using strcmp
    if (strcmp(bs->fs_type, "FAT12") != 0){
	return 0;
    }
    // TODO: Read FAT table from the SD card into array fat_table
    // TODO: Compute root_sector as:
    // num_fat_tables + num_sectors_per_fat + num_reserved_sectors + num_hidden_sectors
}

void fatOpen() {

}

void fatRead() {

}

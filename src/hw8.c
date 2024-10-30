#include "sd.h"
#include "rprintf.h"
#include "serial.h"
#include "fat.h"
#include "string.h"
#define SECTOR_SIZE 512

struct root_directory_entry *current_rde;
struct boot_sector *bs;
char bootSector[SECTOR_SIZE]; // Allocate a global array to store boot sector
char fat_table[8*SECTOR_SIZE];
unsigned int root_sector;
char rde_region[8*SECTOR_SIZE];
struct file current_file;
char file_buf[8*SECTOR_SIZE];

void fatInit() {
    sd_init();
    sd_readblock(0, bootSector, 1); // Read sector 0 from disk drive into bootSector array
    bs = bootSector; // Point boot_sector struct to the boot sector so we can read fields
    esp_printf(putc, "bs: %s", bs);
    // Print out some of the elements of the BIOS information block using rprintf...
    esp_printf(putc, "boot signature: %x\nnumber of fat tables: %i\nnumber of sectors per fat: %i\nnumber of reserved sectors: %i\nnumber of hidden sectors: %i\n", bs->boot_signature, bs->num_fat_tables, bs->num_sectors_per_fat, bs->num_reserved_sectors, bs->num_hidden_sectors);
    // TODO: Validate the boot signature = 0xaa55
    if (bs->boot_signature != 0xaa55) {
        return 0;
    }
    // TODO: Validate fs_type = "FAT12" using strcmp
    if (compareFilenames(bs->fs_type, "FAT12") != 0){
	return 0;
    }
    esp_printf(putc, "Print this if we made it past the checks\n");
    // TODO: Read FAT table from the SD card into array fat_table
    sd_readblock(4, fat_table, 1);
    for(int i = 0; i < SECTOR_SIZE; i++) {
        esp_printf(putc, "%x", fat_table[i]);
    }
    esp_printf(putc, "\n");
    // TODO: Compute root_sector as:
    int root_sector = bs->num_fat_tables + bs->num_sectors_per_fat + bs->num_reserved_sectors + bs->num_hidden_sectors;
}

void fatOpen(char* filepath) {
   //find rde region and read the table into memory
   sd_readblock(root_sector, rde_region, 1);
   //iterate thru table to find the correct rde
   int counter = 0;
   int found = 0;
   while(!found && counter < 8 * SECTOR_SIZE) {
       if(compareFilenames(filepath, rde_region[counter])) {
           found = 1;
	   current_rde = rde_region[counter];
       }
   }
}

void fatRead(char* buf) {
   current_file.rde = *current_rde;
   current_file.start_cluster = current_rde->cluster;
   int offset = -2 + root_sector + current_file.start_cluster * bs->num_sectors_per_cluster;
   sd_readblock(offset , buf, 1);
   for(size_t i = 0; i < sizeof(buf); i++) {
       esp_printf(putc, "%c", buf[i]);
   }
   esp_printf(putc, "\n");
}

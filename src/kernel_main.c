#include "list.h"
#include "rprintf.h"
#include "serial.h"
#include "getEL.c"
#include "page.h"
#include "mmu.h"
#include "sd.h"
#include "gpio.h"
#include "fat.h"
#include "delays.h"

extern struct table_descriptor_stage1 L1table[512];

char glbl[128]; //global variable, defined outside of functions

void clear_bss() { // set all of bss to 0
    extern int __bss_start, __bss_end; //external variables, from kernel.ld
    char *bssstart, *bssend;

    bssstart = &__bss_start;
    bssend = &__bss_end;

    for (int i = 0; i <= bssend - bssstart; i++) {
        bssstart[i] = 0;
    }    
}

void kernel_main() {

    init_pfa_list();

    struct ppage *test = allocate_physical_pages(4);

    free_physical_pages(test);

    mapPages(0, 0);

    loadPageTable(L1table);

    clear_bss();

    wait();

    while(1){
    }
}

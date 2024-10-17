#include "list.h"
#include "rprintf.h"
#include "serial.h"
#include "getEL.c"
#include "page.h"
#include "mmu.h"

extern struct table_descriptor_stage1 L1table[512];

char glbl[128]; //global variable, defined outside of functions

unsigned long get_timer_count() {
     unsigned long *timer_count_register = 0x3f003004;
     return *timer_count_register;
}

void wait() { //waits 1 ms
    int start_time = get_timer_count();
    while(get_timer_count() - start_time < 1000 ){

    }
}

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

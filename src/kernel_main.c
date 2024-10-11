#include "list.h"
#include "rprintf.h"
#include "serial.h"
#include "getEL.c"
#include "page.h"


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

    struct list_element a = {0,0,1};
    struct list_element b = {0,0,2};
    struct list_element *head = &a;
    list_add(&head, &b);
    list_remove(&head, &a);
    list_remove(&head, &b);
    list_add(&head, &a);

    init_pfa_list();

    struct ppage *process1 = allocate_physical_pages(12);

    free_physical_pages(process1);

    esp_printf(putc, "%d", getEL());

    clear_bss();

    wait();

    while(1){
    }
}

#include "list.h"
#include "rprintf.h"
#include "serial.h"
#include "getEL.c"
#include "page.h"

char glbl[128]; //global variable, defined outside of functions

#define NULL 0

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
    struct list_element c = {0,0,3};
    struct list_element *head = &a;

    list_add(&head, &b);
    list_add(&head, &c);

    list_remove(&head, &b);
    list_remove(&head, &c);
    list_remove(&head, &a);

    esp_printf(putc, "%d", getEL());

    clear_bss();

    int time = get_timer_count();

    wait();

    while(1){
    }
}

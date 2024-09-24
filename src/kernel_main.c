#include "list.h"
#include "rprintf.h"
#include "rprintf.c"
#include "serial.c"

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

    unsigned int el;
         asm("mrs %0,CurrentEL"
         : "=r"(el)
         :
         :);

    esp_printf(putc, "hello");

    clear_bss();

    int time = get_timer_count();

    wait();

    while(1){
    }
}

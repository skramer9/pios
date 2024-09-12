
char glbl[128]; //global variable, defined outside of functions


unsigned long get_timer_count() {
     unsigned long *timer_count_register = 0x3f003004;
     return *timer_count_register;
}

wait() { //waits 1 ms
    int time;
}


void kernel_main() {

    extern int __bss_start, __bss_end; //external variables, from kernel.ld
    char *bssstart, *bssend;

    bssstart = &__bss_start;
    bssend = &__bss_end;

    for (int i = 0; i <= bssend - bssstart; i++) { //set bss to clear
        bssstart[i] = 0;
    }

    int time = get_timer_count();

    while(1){
    }
}

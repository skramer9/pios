unsigned long get_timer_count() {
     unsigned long *timer_count_register = 0x3f003004;
     return *timer_count_register;
}

void wait(int ms) {
    unsigned long start_time = get_timer_count();
    while(get_timer_count() - start_time < 1000 * ms){

    }
}


void wait_cycles(int cycles) { 
    unsigned long start_time = get_timer_count();
    while(get_timer_count() - start_time <  cycles){

    }
}

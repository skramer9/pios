#define MU_IO 0x3F215040;

void putc(int data) {
    int *pio = MU_IO; //pointer to the register
    *pio = data; //set the value of the target of the pointer (MU_IO) to data
}

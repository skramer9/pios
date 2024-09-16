char glbl[128]; //global variable, defined outside of functions

#define NULL 0

struct list_element { //element for a linked list
    struct list_element *next;
    int data;
}

//adds an element to a linked list
//@param *list_head = a list_element which points to the first element in the list
//@param *new_element = the new element to be added before its next value (PASS IN THE & OF THE ELEMENT)

list_add(struct list_element *list_head, struct list_element *new_element) {
    struct list_element current = {list_head->next};
    if(new_element->next == NULL) {//if adding an element that doesn't point to anything
        while(current.next->next != current.next) {//go until it reaches the end
            current.next = current.next->next;
            if(current.next == current.next->next) { //if the list only has a head right now, just add it
                break;
            }
        }
        current.next = new_element;
        return;
    }
    if(new_element->next == current.next) {//if adding to the beginning
        current.next = new_element;
        return;
    }
    while(current.next->next != new_element->next) { //while current is not pointing to the thing before the thing to  which new_element is pointing 
        current.next = current.next->next;//make current point to the next item in the list
    }
    current.next->next = new_element;//make the thing to which current is pointing point to new_element
}

//removes an element from a linked list
void list_remove(struct list_element *element) {
    element->data = element->next->data;
    element->next = element->next->next;
}

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

    struct list_element c = {NULL, 3}; // next ptr is NULL, end of list
    struct list_element b = {&c, 2}; // next ptr points to c
    struct list_element a = {&b, 1}; // next ptr points to a
    struct list_element *head = {&a};
    list_add(head, &c);
    list_add(head, &b);
    list_add(head, &a);
    list_remove(&a);
    list_remove(&b);
    list_remove(&c);
    

    clear_bss();

    int time = get_timer_count();

    wait();

    while(1){
    }
}

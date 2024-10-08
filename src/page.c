#include "list.h"
#include "page.h"

#define LENGTH 128

struct ppage physical_page_array[LENGTH]; // 128 pages, each 2mb in length covers 256 megs of memory

struct ppage* init_pfa_list(void) {
    struct ppage *free;
    for(int i = 0; i < LENGTH; i++) {
        list_add(&free, &physical_page_array[i]);
    }
    return free;
}

struct ppage *allocate_physical_pages(struct ppage *free, unsigned int npages) {
    struct ppage *new_list;
    struct ppage *temp;
    for(; npages > 0; npages--) {
        temp = free; //temp pointer to hold the one we are moving
        list_remove(&free, temp); //remove the page
        list_add(&new_list, temp); //add the page from the temp value to new_list
    }
    return new_list;
}

void free_physical_pages(struct ppage *free, struct ppage *ppage_list){
    struct ppage *cursor = ppage_list;
    while(ppage_list) {
        list_remove(&ppage_list, cursor);
        list_add(&free, cursor);
        cursor = cursor->next;
    }
}

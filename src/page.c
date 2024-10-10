#include "list.h"
#include "page.h"

#define LENGTH 128

struct ppage physical_page_array[LENGTH]; // 128 pages, each 2mb in length covers 256 megs of memory

struct ppage *free = 0;

void init_pfa_list(void) {
    for(int i = LENGTH - 1; i >= 0; i--) {
        physical_page_array[i].physical_addr = &physical_page_array[i];
        list_add(&free, &physical_page_array[i]);
    }
}

struct ppage *allocate_physical_pages(unsigned int npages) {
    struct ppage *temp = &free;
    struct ppage *new_list = 0;
    for(; npages > 0; npages--) {
        list_remove(&free, temp); //remove the page
        list_add(&new_list, temp); //add the page from the temp value to new_list
        temp = &free;
    }
    return new_list;
}

void free_physical_pages(struct ppage *ppage_list){
    struct ppage *cursor = ppage_list;
    while(ppage_list) {
        list_remove(&ppage_list, cursor);
        list_add(&free, cursor);
        cursor = cursor->next;
    }
}

#ifndef __PAGE_H
#define __PAGE_H

struct ppage {
    struct ppage *next;
    struct ppage *prev;
    void *physical_addr;
};

void init_pfa_list(void);
void free_physical_pages(struct ppage *ppage_list);
struct ppage *allocate_physical_pages(unsigned int npages);

int fatInit();
void fatOpen();
void fatRead();

#endif

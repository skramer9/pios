#ifndef __PAGE_H
#define __PAGE_H

struct ppage {
    struct ppage *next;
    struct ppage *prev;
    void *physical_addr;
};

struct ppage* init_pfa_list(void);
void free_physical_pages(struct ppage *free, struct ppage *ppage_list);
struct ppage *allocate_physical_pages(struct ppage *free, unsigned int npages);

#endif

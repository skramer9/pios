#ifndef __LIST_H
#define __LIST_H

struct list_element { //element for a linked list
    struct list_element *next;
    struct list_element *prev;
    int data;
};

void list_add(struct list_element **list_head, struct list_element *new_element);
void list_remove(struct list_element **list_head, struct list_element *element);
#endif

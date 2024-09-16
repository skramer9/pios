#include "list.h"

//adds an element to a linked list
void list_add(struct list_element *list_head, struct list_element *new_element) {
    new_element->next = list_head->next;
    list_head->next = &new_element;
}

//removes an element from a linked list
void list_remove(struct list_element *element) {
    element->data = element->next->data;
    element->next = element->next->next;
}


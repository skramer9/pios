#include "list.h"

//adds an element to a linked list
void list_add(struct list_element **list_head, struct list_element *new_element) {
    new_element->next = (*list_head);
    *list_head = new_element;
    new_element->next->prev = new_element;
}

//removes an element from a linked list
void list_remove(struct list_element **list_head, struct list_element *element) {
    if(*list_head == element){
       if(element->next == 0){
            *list_head = 0;
        } else {
            *list_head = element->next;
        }
    }
    element->prev->next = element->next;
    element->next->prev = element->prev;
    element->prev = 0;
    element->next = 0;
}

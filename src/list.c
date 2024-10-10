#include "list.h"

//adds an element to a linked list
void list_add(struct list_element **list_head, struct list_element *new_element) {
    new_element->next = (*list_head); 
    if (*list_head != 0) {
        (*list_head)->prev = new_element;
    }
    *list_head = new_element;
}

//removes an element from a linked list
void list_remove(struct list_element **list_head, struct list_element *element) {
    if(*list_head == element){
        *list_head = element->next;
        if(*list_head != 0){
            (*list_head)->prev = 0;
        }
    } else {
        if(element->prev != 0) {
            element->prev->next = element->next;
        }
        if(element->next != 0) {
            element->next->prev = element->prev;
        }
    }
    element->prev = 0;
    element->next = 0;
}

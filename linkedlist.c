//
// Created by Maximilian Schüller on 21.12.2022.
//

#include "linkedlist.h"
#include "stdlib.h"
#include "stdio.h"

LinkedList list_mkList() {
    LinkedList *list = calloc(1, sizeof(LinkedList));
    list->size=0;
    list->head = NULL;

    return *list;
}

Item *list_mkItem(void *value) {
    Item *newItem = calloc(1, sizeof(Item));
    newItem->value = value;
}

int list_unshift(LinkedList* list, void* value) {
    Item *i = list_mkItem(value);

    i->next = list->head;
    list->head = i;
    list->size++;

    return list->size;
}
int list_push(LinkedList* list, void* value) {
    Item *newItem = list_mkItem(value);

    if(list->size == 0) {
        list->head = newItem;
        list->size++;
        return list->size;
    }

    //Suche letztes Element
    Item *i = list->head;
    while (i->next) {
        i = i->next;
    }

    i->next = newItem;
    list->size++;

    return list->size;
}
int list_addAtIndex(LinkedList* list, void* value, int index) {
    if(list->size <= index) {
        return -1;
    }
    if(index == 0) {
        return list_unshift(list, value);
    }
    if(index == list->size - 1) {
        return list_push(list, value);
    }

    Item *newItem = list_mkItem(value);

    Item *previous = list->head;
    Item *element = list->head->next;
    for (int i = 1; i < index; ++i) {
        previous = element;
        element = element->next;
    }

    previous->next = newItem;
    newItem->next = element;
    list->size++;

    return list->size;
}

void *list_pop(LinkedList* list) {
    if(list->size == 0) {
        return NULL;
    }
    if(list->size == 1) {
        Item *head = list->head;
        list->head = NULL;
        list->size --;
        return head;
    }

    Item *previous;
    Item *i = list->head;
    while (i->next) {
        previous = i;
        i = i->next;
    }

    previous->next = NULL;
    list->size--;

    return i->value;
}
void *list_shift(LinkedList* list) {
    if(list->size == 0) {
        return NULL;
    }
    if(list->size == 1) {
        Item *head = list->head;
        list->head = NULL;
        list->size --;
        return head;
    }

    Item *i = list->head;
    list->head = list->head->next;
    list->size--;

    return i->value;
}
void *list_remove(LinkedList* list, int index) {
    if(list->size <= index) {
        return NULL;
    }
    if(index == list->size - 1) {
        return list_pop(list);
    }
    if(index == 0) {
        return list_shift(list);
    }

    Item *previous = list->head;
    Item *element = list->head->next;
    for (int i = 1; i < index; i++) {
        previous = element;
        element = element->next;
    }

    previous->next = element->next;

    return element->value;
}

void list_reduce();
void list_reverse();
void list_sort();

void *list_get(LinkedList *list, int index) {
    if(list->size <= index) {
        return NULL;
    }

    Item *element = list->head;
    for (int i = 0; i < index; ++i) {
        element = element->next;
    }

    return element->value;
}
void *list_getLast(LinkedList *list) {
    return list_get(list, list->size - 1);
}
void *list_getFirst(LinkedList *list) {
    return list_get(list, 0);
}

void list_print(LinkedList *list) {
    printf("#START LIST\nSize: %d\n", list->size);

    Item *element = list->head;
    for (int i = 0; i < list->size; ++i) {
        printf("\t[%d] -> %s\n", i, (char*)element->value);
        element = element->next;
    }

    printf("#END LIST");
}
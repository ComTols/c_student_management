#include "stdio.h"
//
// Created by Maximilian Schüller on 21.12.2022.
//

#ifndef C_STUDENT_MANAGEMENT_LINKEDLIST_H
#define C_STUDENT_MANAGEMENT_LINKEDLIST_H

typedef struct item {
    void *value;
    struct item *next;
} Item;

typedef struct list {
    int size;
    Item *head;
} LinkedList;

LinkedList list_mkList();
Item *list_mkItem(void *value);

//Fügt ein Element am Anfang hinzu und gibt die neue Länge zurück
int list_unshift(LinkedList* list, void* value);
//Fügt ein Element am Ende hinzu und gibt die neue Länge zurück
int list_push(LinkedList* list, void* value);
//Fügt ein Element an einer bestimmten Position hinzu und gibt die neue Länge zurück
int list_addAtIndex(LinkedList* list, void* value, int index);

//Entfernt das letzte Element und gibt es zurück
void *list_pop(LinkedList* list);
//Entfernt das erste Element und gibt es zurück
void *list_shift(LinkedList* list);
//Entfernt ein Element an einer bestimmten Stelle und gibt es zurück
void *list_remove(LinkedList* list, int index);

//Apply a function simultaneously against two values of the array (from left-to-right) as to reduce it to a single value.
void list_reduce();
//Reverses the order of the elements of an array -- the first becomes the last, and the last becomes the first.
void list_reverse();
//Sorts the elements of an array.
void list_sort();

//Gibt ein Element an einer bestimmten Stelle zurück
void *list_get(LinkedList *list, int index);
void *list_getLast(LinkedList *list);
void *list_getFirst(LinkedList *list);

void list_print(LinkedList *list);


#endif //C_STUDENT_MANAGEMENT_LINKEDLIST_H

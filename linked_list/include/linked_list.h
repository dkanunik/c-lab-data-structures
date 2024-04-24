#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct Node {
    char *item;
    struct Node *next_item;
    struct Node *previous_item;
} Node;

typedef struct {
    Node *first_item;
    Node *last_item;
    size_t size;
} LinkedList;

LinkedList *linked_list_create();

void linked_list_prepend(LinkedList *list, const char *value);

void linked_list_append(LinkedList *list, const char *value);

void linked_list_free(LinkedList *list);

char *linked_list_head(LinkedList *list);

char *linked_list_tail(LinkedList *list);

int linked_list_index_of(LinkedList *list, const char *value);

char *linked_list_value_at(LinkedList *list, int index);

bool linked_list_contains(LinkedList *list, char *value);

char *linked_list_to_array(LinkedList *list, const char *separator);

#endif
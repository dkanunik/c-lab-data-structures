#include "linked_list.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

LinkedList* linked_list_create() {
  LinkedList* list_instance = (LinkedList*)malloc(sizeof(LinkedList));
  if (list_instance == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  list_instance->size = 0;
  list_instance->first_item = NULL;
  list_instance->last_item = NULL;

  return list_instance;
}

void linked_list_free(LinkedList* list) {
  Node* first = list->first_item;
  while (first != NULL) {
    Node* next = first->next_item;
    free(first->item);
    free(first);
    first = next;
  }
  free(list);
}

void linked_list_prepend(LinkedList* list, const char* value) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  if (new_node == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  new_node->item = (char*)malloc(strlen(value) + 1);
  if (new_node->item == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  strcpy(new_node->item, value);

  new_node->previous_item = NULL;
  new_node->next_item = list->first_item;
  list->first_item = new_node;
  if (list->size == 0) {  // case: ll is empty
    list->last_item = new_node;
  }

  list->size++;

  // todo: has to return index
}

void linked_list_append(LinkedList* list, const char* value) {
  Node* new_node = (Node*)malloc(sizeof(Node));
  if (new_node == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  new_node->item = (char*)malloc(strlen(value) + 1);
  if (new_node->item == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  strcpy(new_node->item, value);

  if (list->size > 0) {
    list->last_item->next_item = new_node;
    new_node->previous_item = list->last_item;
  }

  new_node->next_item = NULL;
  list->last_item = new_node;

  if (list->size == 0) {  // case: ll is empty
    list->first_item = new_node;
  }

  list->size++;

  // todo: has to return index
}

char* linked_list_head(LinkedList* list) {
  return list->first_item->item;
}

char* linked_list_tail(LinkedList* list) {
  return list->last_item->item;
}

int linked_list_index_of(LinkedList* list, const char* value) {
  if (list == NULL || list->size == 0 || value == NULL) {
    return -1;
  }

  Node* current = list->first_item;

  int index = 0;

  while (current != NULL) {
    if (strcmp(current->item, value) == 0) {
      return index;
    }
    current = current->next_item;
    index++;
  }

  return -1;
}
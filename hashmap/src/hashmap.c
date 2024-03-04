#include "hashmap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hashmap_free(HashMap *map) {
    for (size_t i = 0; i < map->index_count; i++) {
        KeyValue *current = map->nodes[i];
        while (current != NULL) {
            KeyValue *next = current->next;
            free(current);
            current = next;
        }
    }

    free(map->nodes);
    free(map);
}

size_t hash(const char *key, size_t table_size) {
    size_t hash_value = 0;
    size_t prime = 31;

    while (*key) {
        hash_value = (hash_value * prime + *key) % table_size;
        key++;
    }

    return hash_value;
}

HashMap *hashmap_create() {

    HashMap *map = malloc(sizeof(HashMap));
    if (map == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    map->nodes = (KeyValue **) malloc(INITIAL_CAPACITY * sizeof(KeyValue *));
    if (map->nodes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    map->nodes_count = 0;
    map->index_count = INITIAL_CAPACITY;

    for (int i = 0; i < map->index_count; i++) {
        map->nodes[i] = (KeyValue *) malloc(sizeof(KeyValue));
        if (map->nodes[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        map->nodes[i]->key = NULL;
        map->nodes[i]->value = 0;
        map->nodes[i]->next = NULL;
    }

    return map;
}

bool hashmap_put(HashMap *map, const char *key, int value) {
    if (map == NULL || key == NULL) {
        return false;
    }

    KeyValue *new_node = (KeyValue *) malloc(sizeof(KeyValue));
    if (map->nodes[0] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    map->nodes_count++;

    size_t index = hash(key, map->nodes_count);

    KeyValue *current_node = map->nodes[index];

    new_node->key = key;
    new_node->value = value;
    new_node->next = current_node;

    map->nodes[index] = new_node;

    return true;
}

int *hashmap_get(HashMap *map, const char *key) {
    if (map == NULL || key == NULL) {
        return false;
    }

    int *result = malloc(sizeof(int) * 2);
    result[0] = 0;
    result[1] = 0;

    for (int i = 0; i < map->index_count; ++i) {
        KeyValue *current_node = map->nodes[i];
        while (current_node != NULL) {
            if (current_node->key != NULL && strcmp(current_node->key, key) == 0) {
                result[0] = 1;
                result[1] = current_node->value;
            }
            current_node = current_node->next;
        }
    }

    return result;
}

bool hashmap_remove(HashMap *map, const char *key) {
    if (map == NULL || key == NULL) {
        return false;
    }

    KeyValue* next_node = NULL;

    for (int i = 0; i < map->index_count; ++i) {
        KeyValue* current_node = map->nodes[i];
        while (current_node != NULL) {
            if (current_node->key != NULL && strcmp(current_node->key, key) == 0) {
                if (next_node == NULL) {
                    map->nodes[i] = current_node->next;
                } else {
                    next_node->next = current_node->next;
                }
                free(current_node);
                map->nodes_count--;
                return true;
            }
            next_node = current_node;
            current_node = current_node->next;
        }
    }
    return false;
}
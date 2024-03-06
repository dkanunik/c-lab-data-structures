#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef HASH_MAP_H
#define HASH_MAP_H

#define INITIAL_CAPACITY 50

typedef struct KeyValue {
    const char *key;
    int value;
    struct KeyValue *next;
} KeyValue;

typedef struct {
    size_t index_count;
    size_t nodes_count;
    KeyValue **nodes;
} HashMap;

size_t hash(const char *key, size_t table_size);

HashMap *hashmap_create();

bool hashmap_put(HashMap *map, const char *key, int value);

int *hashmap_get(HashMap *map, const char *key);

bool hashmap_remove(HashMap *map, const char *key);

void hashmap_free(HashMap *map);

int hashmap_size(HashMap *map);

bool hashmap_is_empty(HashMap *map);

char *hashmap_keys(HashMap *map, char *separator);

#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef HASH_MAP_H
#define HASH_MAP_H

#define INITIAL_CAPACITY 50
#define GROWTH_FACTOR 2

typedef struct KeyValue {
  const char* key;
  int value;
  struct KeyValue* next;
} KeyValue;

typedef struct {
  size_t size;
  KeyValue** nodes;
} HashMap;

size_t hash(const char* key, size_t table_size);
HashMap* hashmap_create();
bool hashmap_put(HashMap *map, const char *key, int value);
void hashmap_free(HashMap *map);
#endif

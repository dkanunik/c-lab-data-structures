#include "hashmap.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void hashmap_free(HashMap *map) {
	//todo: release all nodes
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

HashMap* hashmap_create() {

	HashMap *map = malloc(sizeof(HashMap)); 	
	if (map == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

	map->nodes = (KeyValue **)malloc(INITIAL_CAPACITY * sizeof(KeyValue *));
    if (map->nodes == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

	map->size = 0;

	for (int i = 0; i < INITIAL_CAPACITY; i++) {
	    map->nodes[i] = (KeyValue *)malloc(sizeof(KeyValue));
	    if (map->nodes[i] == NULL) {
	        fprintf(stderr, "Memory allocation failed\n");
	        exit(EXIT_FAILURE);
	    }
	    
	    map->nodes[i]->key = '\0';
	    map->nodes[i]->value = 0;
	    map->nodes[i]->next = NULL;	   
	}

	return map;
}

bool hashmap_put(HashMap *map, const char *key, int value) {
	if (map == NULL || key == NULL) {
		return false;
	}

    KeyValue *new_node = (KeyValue *)malloc(sizeof(KeyValue));
    if (map->nodes[0] == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
      
	map->size++;

	size_t index = hash(key, map->size);

	KeyValue *current_node = map->nodes[index];	

	new_node->key = key;
    new_node->value = value;    
    new_node->next = current_node;

	map->nodes[index] = new_node;
	
	printf("\ndebug >> node on map {hash:%li, key:%s, value:%d, address: %p}",
		index, map->nodes[index]->key, map->nodes[index]->value, &map->nodes[index]);

	return true;
}

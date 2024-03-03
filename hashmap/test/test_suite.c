#include <stdlib.h>

#include "hashmap.h"
#include "unity.h"

void setUp() {

}

void tearDown() {

}

void test_hashmap_create(void) {
    HashMap* map = hashmap_create();
    TEST_ASSERT_EQUAL_INT(0, map->size);
    hashmap_free(map);
}

void test_hashmap_put(void) {
    HashMap* map = hashmap_create();
    hashmap_put(map, "test1", 111);
    hashmap_put(map, "test2", 222);
    hashmap_put(map, "test3", 333);
    hashmap_put(map, "test4", 444);
    hashmap_put(map, "test5", 555);
    hashmap_put(map, "test6", 666);
    hashmap_put(map, "test7", 777);
    
    for (size_t i = 0; i < map->size; i++) {
        KeyValue* current = map->nodes[i];
        printf("\nnode[%ld]: {key:%s, value:%d}", i, current->key, current->value);
        
        KeyValue *next = current->next;
        if (next != NULL) {
            printf("\n        next node: {key:%s, value:%d}", next->key, next->value);
        }
    }

    printf("\nnodes size: %ld\n", sizeof(KeyValue));
    TEST_ASSERT_EQUAL_INT(7, map->size);    
}

int main(void) {
  UNITY_BEGIN(); 
  RUN_TEST(test_hashmap_put);
  return UNITY_END();
}

#include <string.h>
#include "heap.h"
#include "unity.h"

Heap *heap = NULL;
int MAX_HEAP_SIZE = 20;

void setUp() {
    heap = heap_create(MAX_HEAP_SIZE);

    int test_data[] = {9, 2, 6,12, 7,1,11,5,15,9,19,17, 4,8};
    int num_elements = sizeof(test_data) / sizeof(test_data[0]);
    for (int i = 0; i < num_elements; i++) {
        heap_insert(heap, test_data[i]);
    }
}

void tearDown() {
    heap_free(heap);
}

void test_heap_create(void) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
    printf("\n");
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_heap_create);
    return UNITY_END();
}

#ifndef HEAP_HEAP_H
#define HEAP_HEAP_H

typedef struct {
    int *array;
    int size;
    int capacity;
} Heap;

void heap_free(Heap *heap);

Heap *heap_create(int capacity);

void heap_percolate_up(Heap *heap, int index);

void heap_insert(Heap* heap, int element);

#endif

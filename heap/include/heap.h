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

int heap_peek(Heap* heap);

void heap_print_as_tree(Heap* heap, int i, int space);

void heap_print_as_row(Heap* heap);

int heap_extract_min(Heap* heap);

void heap_percolate_down(Heap* heap, int index);

int heap_extract_by_index(Heap* heap, int index);

#endif

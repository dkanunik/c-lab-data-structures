#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

Heap* heap_create(int capacity) {
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    if (heap == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    heap->array = (int*)malloc(capacity * sizeof(int));
    if (heap->array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void heap_free(Heap *heap) {
    free(heap->array);
    free(heap);
}

void heap_percolate_up(Heap* heap, int index) {
    while (index > 0) {
        int parent_index = (index - 1) / 2;
        if (heap->array[parent_index] <= heap->array[index])
            break; // Min-heap property satisfied

        // Swap parent and child elements
        heap->array[parent_index] ^= heap->array[index];
        heap->array[index] ^= heap->array[parent_index];
        heap->array[parent_index] ^= heap->array[index];

        index = parent_index;
    }
}

void heap_insert(Heap* heap, int element) {
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Heap is full, cannot insert element\n");
        return;
    }

    // Insert the new element at the end of the heap
    heap->array[heap->size] = element;
    heap->size++;

    // Percolate up to maintain the min-heap property
    heap_percolate_up(heap, heap->size - 1);
}


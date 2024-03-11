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
            break;

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

int heap_peek(Heap* heap) {
    if (heap->size == 0) {
        return -1;
    }
    return heap->array[0];
}

void heap_print_as_tree(Heap* heap, int i, int space) {
    if (i >= heap->size)
        return;

    space += 10;

    heap_print_as_tree(heap, 2 * i + 2, space);

    for (int j = 5; j < space; j++)
        printf(" ");

    printf("%d\n", heap->array[i]);

    heap_print_as_tree(heap, 2 * i + 1, space);
}

void heap_print_as_row(Heap* heap) {
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->array[i]);
    }
}

int heap_extract_min(Heap* heap) {
    if (heap->size == 0) {
        return -1;
    }

    int min_value = heap->array[0];

    heap->array[0] = heap->array[heap->size - 1];
    heap->size--;

    heap_percolate_down(heap, 0);

    return min_value;
}

void heap_percolate_down(Heap* heap, int index) {
    while (index < heap->size) {
        int left_child_index = 2 * index + 1;
        int right_child_index = 2 * index + 2;
        int min_index = index;

        if (left_child_index < heap->size && heap->array[left_child_index] < heap->array[min_index]) {
            min_index = left_child_index;
        }

        if (right_child_index < heap->size && heap->array[right_child_index] < heap->array[min_index]) {
            min_index = right_child_index;
        }

        if (min_index == index) {
            break;
        }

        heap->array[min_index] ^= heap->array[index];
        heap->array[index] ^= heap->array[min_index];
        heap->array[min_index] ^= heap->array[index];

        index = min_index;
    }
}

int heap_extract_by_index(Heap* heap, int index) {
    if (index >= heap->size || index < 0) {
        return -1;
    }

    int extracted_value = heap->array[index];

    heap->array[index] = heap->array[heap->size - 1];
    heap->size--;

    heap_percolate_down(heap, index);

    return extracted_value;
}
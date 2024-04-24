#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack *stack_create() {
    Stack *stack = (Stack *) malloc(sizeof(Stack));

    if (stack == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    stack->storage = (int *) malloc(INITIAL_CAPACITY * sizeof(int));

    if (stack->storage == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    stack->size = 0;
    stack->capacity = INITIAL_CAPACITY;

    for (size_t i = stack->size; i < stack->capacity; ++i) {
        stack->storage[i] = '\0';
    }

    return stack;
}

bool stack_is_empty(const Stack *stack) {
    return stack->size == 0;
}

size_t stack_size(const Stack *stack) {
    return stack->size;
}

void stack_push(Stack *stack, int value) {
    if (stack->size == stack->capacity) {
        size_t new_capacity = stack->capacity * GROWTH_FACTOR;
        int *increased_storage = (int *) realloc(stack->storage, new_capacity * sizeof(int));
        if (increased_storage == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }

        for (size_t i = stack->size; i < new_capacity; ++i) {
            increased_storage[i] = '\0';
        }

        stack->storage = increased_storage;
        stack->capacity = new_capacity;
    }

    for (size_t i = stack->size; i > 0; i--) {
        stack->storage[i] = stack->storage[i - 1];
    }

    stack->storage[0] = value;
    stack->size++;
}

int stack_pop(Stack *stack) {
    if (stack->size > 0) {
        int pop_item = stack->storage[0];

        for (size_t i = 0; i < stack->size; i++) {
            stack->storage[i] = stack->storage[i + 1];
        }

        stack->size--;

        return pop_item;
    } else {
        return '\0';
    }
}

int stack_peek(Stack *stack) {
    if (stack->size > 0) {
        return stack->storage[0];
    } else {
        return '\0';
    }
}

void stack_free(Stack *stack) {
    free(stack->storage);
    free(stack);
}
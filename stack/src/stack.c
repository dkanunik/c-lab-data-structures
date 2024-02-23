#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

Stack* stack_create() {
  Stack* stack = (Stack*)malloc(sizeof(Stack));

  if (stack == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  stack->storage = (int*)malloc(INITIAL_CAPACITY * sizeof(int));

  if (stack->storage == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(EXIT_FAILURE);
  }

  stack->size = 0;
  stack->capacity = INITIAL_CAPACITY;

  return stack;
}

bool stack_is_empty(Stack* stack) {
  return stack->size == 0;
}

size_t stack_size(Stack* stack) {
  return stack->size;
}

void stack_push(Stack* stack, int value) {
  if (stack->size == stack->capacity) {
    size_t new_capacity = stack->capacity * GROWTH_FACTOR;
    int* increased_storage = (int*)realloc(stack->storage, new_capacity * sizeof(int));
    if (increased_storage == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
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

void stack_free(Stack* stack) {
  free(stack->storage);
  free(stack);
}
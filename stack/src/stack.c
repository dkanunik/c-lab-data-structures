#include "stack.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct Stack* stack_create() {
  struct Stack* newStack = (struct Stack*)malloc(sizeof(struct Stack));

  if (newStack == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    return NULL;
  }

  newStack->top = -1;
  return newStack;
}

bool stack_is_empty(struct Stack* stack) {
  if (stack == NULL) {
    return true;
  }

  return (stack->top == -1);
}

size_t stack_size(struct Stack* stack) {
  return sizeof(stack->storage) / sizeof(stack->storage[0]);
}
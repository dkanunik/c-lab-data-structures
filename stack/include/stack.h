#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef STACK_H
#define STACK_H

#define INITIAL_CAPACITY 50
#define GROWTH_FACTOR 2

typedef struct {
  int* storage;
  size_t size;
  size_t capacity;
} Stack;

Stack* stack_create();
bool stack_is_empty(Stack* stack);
size_t stack_size(Stack* stack);
void stack_push(Stack* stack, int value);
void stack_free(Stack* stack);
int stack_pop(Stack* stack);
int stack_peek(Stack* stack);
#endif
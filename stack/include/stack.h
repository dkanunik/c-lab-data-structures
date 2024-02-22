#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifndef STACK_H
#define STACK_H

#define STACK_SIZE 50

struct Stack {
  int top;
  int storage[STACK_SIZE];
};

struct Stack* stack_create();
bool stack_is_empty(struct Stack* stack);
size_t stack_size(struct Stack* stack);
#endif

#include <stdlib.h>

#include "stack.h"
#include "unity.h"

void test_stack_create(void) {
  Stack *stack = stack_create();
  TEST_ASSERT_NOT_NULL(stack);
  TEST_ASSERT_EQUAL_INT(0, stack->size);
  TEST_ASSERT_EQUAL_size_t(10, stack->capacity);
  stack_free(stack);
}

void test_stack_is_empty(void) {
  Stack *stack = stack_create();
  TEST_ASSERT_TRUE(stack_is_empty(stack));
  stack_free(stack);
}

void test_stack_size(void) {
  Stack *stack = stack_create();
  TEST_ASSERT_EQUAL_size_t(0, stack_size(stack));
  stack_free(stack);
}

void test_push(void) {
  Stack *stack = stack_create();

  for (int i = 1; i <= 20; i++) {
    stack_push(stack, i);
  }

  printf("Elements in the stack:\n");
  for (size_t i = 0; i < stack->size; i++) {
    printf("%d ", stack->storage[i]);
  }
  printf("\n");

  TEST_ASSERT_EQUAL_size_t(20, stack_size(stack));
  TEST_ASSERT_EQUAL_size_t(20, stack->capacity);

  stack_free(stack);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_stack_create);
  RUN_TEST(test_stack_is_empty);
  RUN_TEST(test_stack_size);
  RUN_TEST(test_push);
  return UNITY_END();
}

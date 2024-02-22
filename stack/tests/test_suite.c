#include <stdlib.h>

#include "stack.h"
#include "unity.h"

void test_stack_create(void) {
  struct Stack* stack = stack_create();
  TEST_ASSERT_NOT_NULL(stack);
  TEST_ASSERT_EQUAL_INT(-1, stack->top);
  free(stack);
}

void test_stack_is_empty(void) {
  struct Stack* stack = stack_create();
  TEST_ASSERT_TRUE(stack_is_empty(stack));
  free(stack);
}

void test_stack_size(void) {
  struct Stack* stack = stack_create();
  TEST_ASSERT_EQUAL_size_t(50, stack_size(stack));
  free(stack);
}

int main(void) {
  UNITY_BEGIN();
  RUN_TEST(test_stack_create);
  RUN_TEST(test_stack_is_empty);
  RUN_TEST(test_stack_size);
  return UNITY_END();
}

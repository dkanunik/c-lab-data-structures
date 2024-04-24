#include "stack.h"
#include "unity/unity.h"

Stack *stack = NULL;

void setUp() {
    stack = stack_create();
}

void tearDown() {
    stack_free(stack);
}


void test_stack_create(void) {
    TEST_ASSERT_NOT_NULL(stack);
    TEST_ASSERT_EQUAL_INT(0, stack->size);
    TEST_ASSERT_EQUAL_size_t(50, stack->capacity);
}

void test_stack_is_empty(void) {
    TEST_ASSERT_TRUE(stack_is_empty(stack));
}

void test_stack_size(void) {
    TEST_ASSERT_EQUAL_size_t(0, stack_size(stack));
}

void test_stack_push(void) {
    for (int i = 0; i <= 20; i++) {
        stack_push(stack, i);
    }

    printf("\nElements in the stack:\n");
    for (size_t i = 0; i < stack->size; i++) {
        printf("%d ", stack->storage[i]);
    }
    printf("\n");

    TEST_ASSERT_EQUAL_size_t(21, stack_size(stack));
    TEST_ASSERT_EQUAL_size_t(50, stack->capacity);
}

void test_stack_pop(void) {
    for (int i = 0; i < 5; i++) {
        stack_push(stack, i);
    }

    printf("\nInit stack:\n");
    for (size_t i = 0; i < stack->size; i++) {
        printf("%d ", stack->storage[i]);
    }
    printf("\n");

    TEST_ASSERT_EQUAL_size_t(5, stack_size(stack));

    int pop_value = stack_pop(stack);

    printf("Stack after pop:\n");
    for (size_t i = 0; i < stack->size; i++) {
        printf("%d ", stack->storage[i]);
    }
    printf("\n");

    TEST_ASSERT_EQUAL_INT(4, pop_value);
    TEST_ASSERT_EQUAL_INT(0, stack->storage[4]);
    TEST_ASSERT_EQUAL_INT(0, stack->storage[4]);
    TEST_ASSERT_EQUAL_size_t(4, stack_size(stack));
}

void test_stack_peek(void) {
    for (int i = 0; i <= 10; i++) {
        stack_push(stack, i);
        printf("\n%d", i);
    }

    TEST_ASSERT_EQUAL_INT(10, stack_peek(stack));
    TEST_ASSERT_EQUAL_size_t(11, stack_size(stack));
    stack_push(stack, 100);
    TEST_ASSERT_EQUAL_INT(100, stack_peek(stack));
    TEST_ASSERT_EQUAL_size_t(12, stack_size(stack));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_stack_create);
    RUN_TEST(test_stack_is_empty);
    RUN_TEST(test_stack_size);
    RUN_TEST(test_stack_push);
    RUN_TEST(test_stack_peek);
    RUN_TEST(test_stack_pop);
    return UNITY_END();
}

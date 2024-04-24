#include <stdio.h>
#include <string.h>

#include "linked_list.h"
#include "unity/unity.h"

LinkedList *list = NULL;

void setUp() {
    list = linked_list_create();
}

void tearDown() {
    linked_list_free(list);
}

void test_linked_list_create(void) {
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(0, list->size);
    TEST_ASSERT_NULL(list->first_item);
    TEST_ASSERT_NULL(list->last_item);
}

void test_linked_list_head(void) {
    char text[] = "qwerty";
    linked_list_prepend(list, text);
    char const *head = linked_list_head(list);

    TEST_ASSERT_EQUAL_STRING(text, head);
}

void test_linked_list_tail(void) {
    char text[] = "qwerty";
    linked_list_prepend(list, text);
    char const *tail = linked_list_tail(list);
    TEST_ASSERT_EQUAL_STRING(text, tail);
}

/**
 * init
 * prepend
 * check last in the list
 * check first in the list
 */
void test_linked_list_prepend_1(void) {
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(0, list->size);
    TEST_ASSERT_NULL(list->first_item);
    TEST_ASSERT_NULL(list->last_item);

    char text[] = "qwerty";
    linked_list_prepend(list, text);

    TEST_ASSERT_EQUAL_size_t(1, list->size);
    TEST_ASSERT_EQUAL_STRING(text, linked_list_tail(list));
    TEST_ASSERT_EQUAL_STRING(text, linked_list_head(list));
}

/**
 * init
 * prepend, prepend, prepend
 * check last in the list
 * check first in the list
 */
void test_linked_list_prepend_3(void) {
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(0, list->size);
    TEST_ASSERT_NULL(list->first_item);
    TEST_ASSERT_NULL(list->last_item);

    char text1[] = "qwerty1";
    linked_list_prepend(list, text1);

    char text2[] = "asdfg2";
    linked_list_prepend(list, text2);

    char text3[] = "zxcvb3";
    linked_list_prepend(list, text3);

    TEST_ASSERT_EQUAL_size_t(3, list->size);
    TEST_ASSERT_EQUAL_STRING(text3, linked_list_head(list));
    TEST_ASSERT_EQUAL_STRING(text1, linked_list_tail(list));
}

/**
 * init
 * append
 * check last in the list
 * check first in the list
 */
void test_linked_list_append_1(void) {
    TEST_ASSERT_NOT_NULL(list);
    TEST_ASSERT_EQUAL_size_t(0, list->size);
    TEST_ASSERT_NULL(list->first_item);
    TEST_ASSERT_NULL(list->last_item);

    char text1[] = "qwerty1";
    linked_list_append(list, text1);

    TEST_ASSERT_EQUAL_size_t(1, list->size);
    TEST_ASSERT_EQUAL_STRING(text1, list->last_item->item);
    TEST_ASSERT_EQUAL_INT(0, strcmp(text1, list->last_item->item));
    TEST_ASSERT_EQUAL_STRING(text1, linked_list_tail(list));
    TEST_ASSERT_EQUAL_STRING(text1, linked_list_head(list));
}

/**
 * init
 * append, append, append
 * check last in the list
 */
void test_linked_list_append_3(void) {
    char text1[] = "qwerty1";
    linked_list_append(list, text1);

    char text2[] = "asdfg2";
    linked_list_append(list, text2);

    char text3[] = "zxcvb3";
    linked_list_append(list, text3);

    TEST_ASSERT_EQUAL_size_t(3, list->size);
    TEST_ASSERT_EQUAL_STRING(text3, linked_list_tail(list));
    TEST_ASSERT_EQUAL_STRING(text1, linked_list_head(list));
}

/**
 * init
 * append, append
 * check the first coincidence
 */
void test_linked_list_index_for_2_append(void) {
    char text1[] = "qwerty1";
    linked_list_append(list, text1);

    char text2[] = "qwerty2";
    linked_list_append(list, text2);

    int index = linked_list_index_of(list, text2);

    TEST_ASSERT_EQUAL_INT(1, index);
}

/**
 * init
 * prepend, prepend
 * check the first coincidence
 */
void test_linked_list_index_for_2_prepend(void) {
    char text1[] = "qwerty1";
    linked_list_prepend(list, text1);

    char text2[] = "qwerty2";
    linked_list_prepend(list, text2);

    int index = linked_list_index_of(list, text2);

    TEST_ASSERT_EQUAL_INT(0, index);
}

/**
 * init
 * prepend, prepend
 * check index of element with the value
 */
void test_linked_list_value_at_2_prepend(void) {
    char text1[] = "qwerty1";
    linked_list_prepend(list, text1);

    char text2[] = "qwerty2";
    linked_list_prepend(list, text2);

    char const *value1 = linked_list_value_at(list, 1);

    TEST_ASSERT_EQUAL_STRING(text1, value1);
}

void test_linked_list_contains(void) {
    char text1[] = "qwerty1";
    linked_list_append(list, text1);

    char text2[] = "qwerty2";
    linked_list_append(list, text2);

    char text3[] = "qwerty3";
    linked_list_append(list, text3);

    TEST_ASSERT_TRUE(linked_list_contains(list, text2));
    TEST_ASSERT_FALSE(linked_list_contains(list, "test"));
}

void test_linked_list_to_array(void) {
    linked_list_append(list, "qwerty1");
    linked_list_append(list, "qwerty2");
    linked_list_append(list, "qwerty3");

    const char *separator = ", ";
    const char *expected_result = "qwerty1, qwerty2, qwerty3";
    char const *actual_result = linked_list_to_array(list, separator);

    TEST_ASSERT_EQUAL_STRING(expected_result, actual_result);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_linked_list_create);
    RUN_TEST(test_linked_list_prepend_1);
    RUN_TEST(test_linked_list_head);
    RUN_TEST(test_linked_list_prepend_3);
    RUN_TEST(test_linked_list_append_1);
    RUN_TEST(test_linked_list_tail);
    RUN_TEST(test_linked_list_append_3);
    RUN_TEST(test_linked_list_index_for_2_append);
    RUN_TEST(test_linked_list_index_for_2_prepend);
    RUN_TEST(test_linked_list_value_at_2_prepend);
    RUN_TEST(test_linked_list_contains);
    RUN_TEST(test_linked_list_to_array);
    return UNITY_END();
}

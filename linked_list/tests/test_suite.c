#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "unity.h"

void test_linked_list_create(void) {
  LinkedList *list = linked_list_create();

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL_size_t(0, list->size);
  TEST_ASSERT_NULL(list->first_item);
  TEST_ASSERT_NULL(list->last_item);

  linked_list_free(list);
}

void test_linked_list_head(void) {
  LinkedList *list = linked_list_create();

  char text[] = "qwerty";
  linked_list_prepend(list, text);
  char *head = linked_list_head(list);

  TEST_ASSERT_EQUAL_STRING(text, head);

  linked_list_free(list);
}

void test_linked_list_tail(void) {
  LinkedList *list = linked_list_create();

  char text[] = "qwerty";
  linked_list_prepend(list, text);
  char *tail = linked_list_tail(list);
  TEST_ASSERT_EQUAL_STRING(text, tail);

  linked_list_free(list);
}

/**
 * init
 * prepend
 * check last in the list
 * check first in the list
 */
void test_linked_list_prepend_1(void) {
  LinkedList *list = linked_list_create();

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL_size_t(0, list->size);
  TEST_ASSERT_NULL(list->first_item);
  TEST_ASSERT_NULL(list->last_item);

  char text[] = "qwerty";
  linked_list_prepend(list, text);

  TEST_ASSERT_EQUAL_size_t(1, list->size);
  // verify last node

  TEST_ASSERT_EQUAL_STRING(text, linked_list_tail(list));

  // verify first node
  TEST_ASSERT_EQUAL_STRING(text, linked_list_head(list));

  linked_list_free(list);
}

/**
 * init
 * prepend, prepend, prepend
 * check last in the list
 * check first in the list
 */
void test_linked_list_prepend_3(void) {
  LinkedList *list = linked_list_create();

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

  // verify first node
  TEST_ASSERT_EQUAL_STRING(text3, linked_list_head(list));

  // verify last node
  TEST_ASSERT_EQUAL_STRING(text1, linked_list_tail(list));

  linked_list_free(list);
}

/**
 * init
 * append
 * check last in the list
 * check first in the list
 */
void test_linked_list_append_1(void) {
  LinkedList *list = linked_list_create();

  TEST_ASSERT_NOT_NULL(list);
  TEST_ASSERT_EQUAL_size_t(0, list->size);
  TEST_ASSERT_NULL(list->first_item);
  TEST_ASSERT_NULL(list->last_item);

  char text1[] = "qwerty1";
  linked_list_append(list, text1);

  TEST_ASSERT_EQUAL_size_t(1, list->size);
  TEST_ASSERT_EQUAL_STRING(text1, list->last_item->item);
  TEST_ASSERT_EQUAL_INT(0, strcmp(text1, list->last_item->item));

  // verify last node
  TEST_ASSERT_EQUAL_STRING(text1, linked_list_tail(list));

  // verify first node
  TEST_ASSERT_EQUAL_STRING(text1, linked_list_head(list));

  linked_list_free(list);
}

/**
 * init
 * append, append, append
 * check last in the list
 */
void test_linked_list_append_3(void) {
  LinkedList *list = linked_list_create();

  char text1[] = "qwerty1";
  linked_list_append(list, text1);

  char text2[] = "asdfg2";
  linked_list_append(list, text2);

  char text3[] = "zxcvb3";
  linked_list_append(list, text3);

  TEST_ASSERT_EQUAL_size_t(3, list->size);

  // verify last node
  TEST_ASSERT_EQUAL_STRING(text3, linked_list_tail(list));

  // verify first node
  TEST_ASSERT_EQUAL_STRING(text1, linked_list_head(list));

  linked_list_free(list);
}

/**
 * init
 * append, append
 * check the first coincidence
 */
void test_linked_list_index_for_2_append(void) {
  LinkedList *list = linked_list_create();

  char text1[] = "qwerty1";
  linked_list_append(list, text1);

  char text2[] = "qwerty2";
  linked_list_append(list, text2);

  int index = linked_list_index_of(list, text2);

  TEST_ASSERT_EQUAL_INT(1, index);

  linked_list_free(list);
}

/**
 * init
 * prepend, prepend
 * check the first coincidence
 */
void test_linked_list_index_for_2_prepend(void) {
  LinkedList *list = linked_list_create();

  char text1[] = "qwerty1";
  linked_list_prepend(list, text1);

  char text2[] = "qwerty2";
  linked_list_prepend(list, text2);

  int index = linked_list_index_of(list, text2);

  TEST_ASSERT_EQUAL_INT(0, index);

  linked_list_free(list);
}

/**
 * init
 * prepend, prepend
 * check index of element with the value
 */
void test_linked_list_value_at_2_prepend(void) {
  LinkedList *list = linked_list_create();

  char text1[] = "qwerty1";
  linked_list_prepend(list, text1);

  char text2[] = "qwerty2";
  linked_list_prepend(list, text2);

  char *value1 = linked_list_value_at(list, 1);

  TEST_ASSERT_EQUAL_STRING(text1, value1);
  linked_list_free(list);
}

void test_linked_list_contains(void) {
  LinkedList *list = linked_list_create();

  char text1[] = "qwerty1";
  linked_list_append(list, text1);

  char text2[] = "qwerty2";
  linked_list_append(list, text2);

  char text3[] = "qwerty3";
  linked_list_append(list, text3);

  TEST_ASSERT_TRUE(linked_list_contains(list, text2));
  TEST_ASSERT_FALSE(linked_list_contains(list, "test"));
  linked_list_free(list);
}

void test_linked_list_to_array(void) {
  LinkedList *list = linked_list_create();

  linked_list_append(list, "qwerty1");
  linked_list_append(list, "qwerty2");
  linked_list_append(list, "qwerty3");

  const char *separator = ", ";
  const char *expected_result = "qwerty1, qwerty2, qwerty3";
  char *actual_result = linked_list_to_array(list, separator);

  TEST_ASSERT_EQUAL_STRING(expected_result, actual_result);
  printf("%s\n", actual_result);

  linked_list_free(list);
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

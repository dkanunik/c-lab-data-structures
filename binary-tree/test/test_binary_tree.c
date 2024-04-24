#include <stdlib.h>
#include "unity/unity.h"
#include "binary_tree.h"

BinaryTree* tree = NULL;

void tearDown() {
    tree_destroy(tree);
}

void setUp() {
    tree = tree_create();

    tree_insert(tree, 1);
    tree_insert(tree, 3);
    tree_insert(tree, 12);
    tree_insert(tree, 9);
    tree_insert(tree, 18);
    tree_insert(tree, 2);
    tree_insert(tree, 8);
    tree_insert(tree, 7);
    tree_insert(tree, 20);
}

void test_size_height() {
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 9);
    TEST_ASSERT_EQUAL_INT(tree_height(tree->root), 6);
}

void test_tree_min_max() {
    TEST_ASSERT_EQUAL_INT(tree_get_min(tree->root), 1);
    TEST_ASSERT_EQUAL_INT(tree_get_max(tree->root), 20);
}

void test_remove() {
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 9);
    TEST_ASSERT_TRUE(tree_search(tree->root, 9));
    tree_remove(tree->root, 9);
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 8);
    TEST_ASSERT_FALSE(tree_search(tree->root, 9));
}

void test_tree_clear() {
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 9);
    tree_clear(tree->root);
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 9);
    TEST_ASSERT_FALSE(tree_is_empty(tree));
    TEST_ASSERT_EQUAL_INT(tree_get_min(tree->root), 0);
    TEST_ASSERT_EQUAL_INT(tree_get_max(tree->root), 0);
}

void test_tree_traverse_preorder() {
    int expected[] = {1, 3, 2, 12, 9, 8, 7, 18, 20};
    int index = 0;
    size_t size = tree_size(tree->root);
    int *actual = (int*)calloc(size, sizeof(int));
        if (actual == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    tree_traverse_preorder(tree->root, actual, &index);
    for (int i = 0; i < size; i++) {
        printf("%d ", actual[i]);
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, size);
    free(actual);
}

void test_tree_traverse_inorder() {
    int expected[] = {1, 2, 3, 7, 8, 9, 12, 18, 20};
    int index = 0;
    size_t size = tree_size(tree->root);
    int *actual = (int*)calloc(size, sizeof(int));
    if (actual == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    tree_traverse_inorder(tree->root, actual, &index);
    for (int i = 0; i < size; i++) {
        printf("%d ", actual[i]);
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, size);
    free(actual);
}

void test_tree_traverse_postorder() {
    int expected[] = {2, 7, 8, 9, 20, 18, 12, 3, 1};
    int index = 0;
    size_t size = tree_size(tree->root);
    int *actual = (int*)calloc(size, sizeof(int));
    if (actual == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    tree_traverse_postorder(tree->root, actual, &index);
    for (int i = 0; i < size; i++) {
        printf("%d ", actual[i]);
    }
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, size);
    free(actual);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_size_height);
    RUN_TEST(test_tree_min_max);
    RUN_TEST(test_remove);
    RUN_TEST(test_tree_clear);
    RUN_TEST(test_tree_traverse_preorder);
    RUN_TEST(test_tree_traverse_inorder);
    RUN_TEST(test_tree_traverse_postorder);
    return UNITY_END();
}

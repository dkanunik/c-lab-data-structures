#include <stdlib.h>
#include "unity.h"
#include "binary_tree.h"

BinaryTree* tree = NULL;

void tearDown() {
    tree_destroy(tree);
}

void setUp() {
    tree = tree_create();
}

void test_size_height() {
    tree_insert(tree, 1);
    tree_insert(tree, 3);
    tree_insert(tree, 7);
    tree_insert(tree, 2);
    tree_insert(tree, 9);
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 5);
    TEST_ASSERT_EQUAL_INT(tree_height(tree->root), 4);
}

void test_tree_min_max() {
    tree_insert(tree, 10);
    tree_insert(tree, 3);
    tree_insert(tree, 70);
    tree_insert(tree, 2);
    tree_insert(tree, 90);
    tree_insert(tree, 9);
    TEST_ASSERT_EQUAL_INT(tree_get_min(tree->root), 2);
    TEST_ASSERT_EQUAL_INT(tree_get_max(tree->root), 90);
}

void test_remove() {
    tree_insert(tree, 1);
    tree_insert(tree, 3);
    tree_insert(tree, 12);
    tree_insert(tree, 9);
    tree_insert(tree, 18);
    tree_insert(tree, 2);
    tree_insert(tree, 8);
    tree_insert(tree, 7);
    tree_insert(tree, 20);
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 9);
    TEST_ASSERT_TRUE(tree_search(tree->root, 9));
    tree_remove(tree->root, 9);
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 8);
    TEST_ASSERT_FALSE(tree_search(tree->root, 9));
}

void test_tree_clear() {
    tree_insert(tree, 1);
    tree_insert(tree, 3);
    tree_insert(tree, 7);
    tree_insert(tree, 2);
    tree_insert(tree, 9);
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 5);
    tree_clear(tree->root);
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 5);
    TEST_ASSERT_FALSE(tree_is_empty(tree));
    TEST_ASSERT_EQUAL_INT(tree_get_min(tree->root), 0);
    TEST_ASSERT_EQUAL_INT(tree_get_max(tree->root), 0);
}

void test_tree_traverse_preorder() {
    tree_insert(tree, 1);
    tree_insert(tree, 3);
    tree_insert(tree, 12);
    tree_insert(tree, 9);
    tree_insert(tree, 18);
    tree_insert(tree, 2);
    tree_insert(tree, 8);
    tree_insert(tree, 7);
    tree_insert(tree, 20);

    int index = 0;
    size_t size = tree_size(tree->root);
    int *arr = (int*)calloc(size, sizeof(int));
        if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    tree_traverse_preorder(tree->root, arr, &index);
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    //todo: check output
    free(arr);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_size_height);
    RUN_TEST(test_tree_min_max);
    RUN_TEST(test_remove);
    RUN_TEST(test_tree_clear);
    RUN_TEST(test_tree_traverse_preorder);
    return UNITY_END();
}

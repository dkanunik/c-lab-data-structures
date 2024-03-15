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
    tree_remove(tree->root, 9);
    TEST_ASSERT_EQUAL_INT(tree_size(tree->root), 8);
    //todo: use tree_search() when it will be implemented
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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_size_height);
    RUN_TEST(test_tree_min_max);
    RUN_TEST(test_remove);
    RUN_TEST(test_tree_clear);
    return UNITY_END();
}

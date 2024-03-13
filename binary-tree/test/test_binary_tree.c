#include "unity.h"
#include "binary_tree.h"

BinaryTree* tree = NULL;

void tearDown() {
    tree_destroy(tree);
}

void setUp() {
    tree = tree_create();
}

void test_tree_insert() {
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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_tree_insert);
    RUN_TEST(test_tree_min_max);
    return UNITY_END();
}

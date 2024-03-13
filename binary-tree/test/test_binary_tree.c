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
    TEST_ASSERT_EQUAL_INT(tree->root->value, 1);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_tree_insert);
    return UNITY_END();
}

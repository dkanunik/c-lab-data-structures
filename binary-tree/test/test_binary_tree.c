#include "unity.h"
#include "binary_tree.h"

BinaryTree* tree = NULL;

void tearDown() {
    tree_destroy(tree);
}

void setUp() {
    tree = tree_create();
}

int main(void) {
    UNITY_BEGIN();
    return UNITY_END();
}

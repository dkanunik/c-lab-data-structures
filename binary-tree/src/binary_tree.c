#include <stddef.h>
#include <malloc.h>
#include <stdlib.h>
#include "binary_tree.h"

BinaryTree* tree_create() {

    BinaryTree* tree = (BinaryTree *) malloc(sizeof(BinaryTree));
    if (tree == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    tree->root = NULL;
    return tree;
}

void tree_destroy(BinaryTree* tree) {
    if (tree == NULL) {
        return;
    }
    tree_nodes_destroy(tree->root);
    free(tree);
}

void tree_nodes_destroy(TreeNode* node) {
    if (node == NULL) {
        return;
    }

    tree_nodes_destroy(node->left);
    tree_nodes_destroy(node->right);

    free(node);
}

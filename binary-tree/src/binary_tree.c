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


int tree_insert(BinaryTree* tree, int value) {
    if (tree == NULL) {
        return -1;
    }

    TreeNode* new_node = tree_create_node(value);

    if (tree->root == NULL) {
        tree->root = new_node;
        return 0;
    }

    TreeNode* current = tree->root;
    TreeNode* parent = tree->root;
    while (current != NULL) {
        parent = current;
        if (value < current->value) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (value < parent->value) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
    return 1;
}

TreeNode* tree_create_node(int value) {
    TreeNode* new_node = (TreeNode*)malloc(sizeof(TreeNode));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    new_node->value = value;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}
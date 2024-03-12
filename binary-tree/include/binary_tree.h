#include <stddef.h>

#ifndef BINARY_TREE_BINARY_TREE_H
#define BINARY_TREE_BINARY_TREE_H

typedef struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    struct TreeNode *root;
} BinaryTree;

BinaryTree* tree_create();
void tree_destroy(BinaryTree* tree);
void tree_nodes_destroy(TreeNode* node);

#endif

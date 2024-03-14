#include <stddef.h>
#include <stdbool.h>

#ifndef BINARY_TREE_BINARY_TREE_H
#define BINARY_TREE_BINARY_TREE_H

typedef struct TreeNode {
    int value;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct {
    struct TreeNode *root;
} BinaryTree;

BinaryTree* tree_create();
TreeNode* tree_create_node(int value);
int tree_insert(BinaryTree* tree, int value);
void tree_destroy(BinaryTree* tree);
void tree_nodes_destroy(TreeNode* node);
size_t tree_size(TreeNode* node);
int tree_height(TreeNode* root);
int tree_get_min(TreeNode* node);
int tree_get_max(TreeNode *node);
void tree_clear(TreeNode* node);
bool tree_is_empty(BinaryTree *tree);

#endif
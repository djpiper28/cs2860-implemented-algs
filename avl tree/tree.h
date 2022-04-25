#pragma once

#define max(a, b) (((a >= b) * a) + ((b > a) * b))

typedef struct tree_node {
    struct tree_node *l;
    struct tree_node *r;
    int payload;
} tree_node;

tree_node *init_tree_node();
int tree_height(tree_node *node);
int tree_balance(tree_node *node);
void free_tree(tree_node *tree);
void print_tree(tree_node *root);


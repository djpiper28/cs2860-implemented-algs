#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void free_tree(tree_node *tree)
{
    if (tree->l) free_tree(tree->l);
    if (tree->r) free_tree(tree->r);

    free(tree);
}

int tree_balance(tree_node *root)
{
    if (!root) return 0;

    int lh, rh;
    lh = rh = 0;

    if (root->l) lh = tree_height(root->l);
    if (root->r) rh = tree_height(root->r);

    return lh - rh;
}

int __tree_height(tree_node *node, int h)
{
    int h1, h2;
    h2 = h1 = 0;

    if (node->l) {
        h1 = __tree_height(node->l, h + 1);
    }

    if (node->r) {
        h2 = __tree_height(node->r, h + 1);
    }

    int ret = max(h1, h2);
    // Check for leaf
    if (ret == 0) {
        return h + 1;
    } else {
        return ret;
    }
}

int tree_height(tree_node *node)
{
    return __tree_height(node, 0);
}

tree_node *init_tree_node()
{
    tree_node *tree = malloc(sizeof * tree);
    memset(tree, 0, sizeof * tree);
    return tree;
}

void __print_tree(tree_node *tree, int h)
{
    for (int i = 0; i < h; i++) printf("  |");
    printf("  |> %d\n", tree->payload);

    if (tree->l) __print_tree(tree->l, h + 1);
    else puts("--");
    if (tree->r) __print_tree(tree->r, h + 1);
    else puts("--");
}

void print_tree(tree_node *root)
{
    __print_tree(root, 0);
}


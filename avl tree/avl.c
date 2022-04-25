#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

void rotate_l(tree_node *root)
{
    /* Rotation (left):
      x            y
    y   c  ->    x   b
  a   b        a   c
     */
    int tmp = root->l->payload;
    root->l->payload = root->payload;
    root->payload = tmp;

    tree_node *tmp2 = root->l->r;
    root->l->r = root->r;
    root->r = tmp2;
}

void rotate_r(tree_node *root)
{
    /* Rotation (right):
       x            y
     a   y  ->    b   x
       b   c        a   c
     */
    int tmp = root->r->payload;
    root->r->payload = root->payload;
    root->payload = tmp;

    tree_node *tmp2 = root->r->l;
    root->r->l = root->l;
    root->l = tmp2;
}

void insert_node(tree_node *root, tree_node *node)
{
    if (node->payload < root->payload) {
        // Add left
        if (root->l) {
            insert_node(root->l, node);
        } else {
            root->l = node;
            return;
        }
    } else {
        // Add right
        if (root->r) {
            insert_node(root->r, node);
        } else {
            root->r = node;
            return;
        }
    }

    // Balance trees
    int balance = tree_balance(root);
    if (balance > 1) {
        if (tree_balance(root->l) > 0) {
            rotate_l(root);
        } else {
            rotate_l(root);
            rotate_r(root);
        }
    } else if (balance < -1) {
        if (tree_balance(root->r) > 0) {
            rotate_r(root);
            rotate_l(root);
        } else {
            rotate_r(root);
        }
    }
}

int main(int argc, char **argv)
{
    if (argc == 1) {
        fprintf(stderr, "Usage: %s NUM NUM ...\n", argv[0]);
        return 1;
    }

    tree_node *tree = init_tree_node();

    // Add to tree
    for (int i = 1; i < argc; i++) {
        int num = abs(atoi(argv[i]));
        if (num == 0) {
            num = 1;
        }

        printf("Adding %d to tree\n", num);

        if (i == 1) {
            tree->payload = num;
        } else {
            tree_node *node = init_tree_node();
            node->payload = num;
            insert_node(tree, node);
        }
        print_tree(tree);
    }

    printf("Tree height %d\n", tree_height(tree));

    free_tree(tree);
    return 1;
}


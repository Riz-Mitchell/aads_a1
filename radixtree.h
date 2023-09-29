#include "data.h"
#include "binops.h"

#ifndef _RADIXTREE_H_
#define _RADIXTREE_H_

typedef struct node node_t;

struct node {
    int n_bits;
    char *prefix;
    business_t data;
    node_t *branchA;
    node_t *branchB;
};

typedef struct tree {
    node_t *root;
} tree_t;

tree_t* data_to_tree(FILE *data_file, tree_t *tree);
void data_to_node(int field_num, char *field, node_t *curr_node);
void insert_node(tree_t *tree, node_t *node);

#endif
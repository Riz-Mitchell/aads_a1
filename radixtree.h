#include "data.h"
#include "binops.h"
#include <string.h>

#ifndef _RADIXTREE_H_
#define _RADIXTREE_H_

typedef struct branch branch_t;

struct branch {
    int prefix_bits;
    char *prefix;
    business_t data;
    branch_t *branchA;        // "right side"
    branch_t *branchB;        // "left side"
};

typedef struct tree {
    branch_t *root;
} tree_t;

tree_t* create_tree();
void free_tree(branch_t *root);
tree_t* data_to_tree(FILE *data_file, tree_t *tree, FILE *output_file);
void data_to_branch(int field_num, char *field, branch_t *curr_branch);
tree_t* insert_branch(tree_t *tree, branch_t *inserting);
int compare_prefix(char *curr_prefix, char *insert_prefix);
branch_t* split_branches(branch_t *curr, branch_t *inserting);
char* get_common_prefix(char *curr_prefix, char *insert_prefix);
char* remove_bits(char *prefix, int bits);
void output_tree(branch_t *root, FILE *output_file);


#endif
#include "data.h"
#include "binops.h"
#include <string.h>

#ifndef _TREE_H_
#define _TREE_H_

typedef struct branch branch_t;

struct branch {
    int prefix_bits;
    char *prefix;
    business_t *data;
    branch_t *branchA;        // "right side"
    branch_t *branchB;        // "left side"
};

typedef struct tree {
    branch_t *root;
} tree_t;

#endif
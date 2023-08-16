#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "string.h"
#include "utils.h"

#ifndef _LIST_H_
#define _LIST_H_

typedef struct node node_t;
struct node {
    business_t business;
    node_t *next;
};

typedef struct list {
    node_t *head;
    node_t *tail;
} list_t;

// Function Definitions
list_t* make_LL (void);
void free_LL (list_t *list);
list_t* node_to_list(list_t *list, node_t *curr_node);
node_t* data_to_node(int field_num, char *field, node_t *curr_node);
void free_strings(node_t *business_node);
int list_search(list_t *list, char *query, FILE *output_file);
list_t* dataset_to_list (FILE *data_file);

#endif
#include "data.h"

#ifndef _LIST_H_
#define _LIST_H_

typedef struct node node_t;
struct node {
    business_t *business;
    node_t *next;
};

typedef struct list {
    node_t *head;
    node_t *tail;
} list_t;

// Function Definitions
list_t* make_LL (void);
void free_LL (list_t *list);
list_t* insert_business (list_t *list, node_t *business_node);
void print_list(list_t *list);
node_t* insert_field (char *field, int field_num, node_t *business_node);
void free_business (node_t *business_node);

#endif
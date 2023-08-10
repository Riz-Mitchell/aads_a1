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
list_t* insert_business (list_t *list, business_t *business_data);
#endif
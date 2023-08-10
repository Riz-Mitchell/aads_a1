#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "data.h"

typedef struct node node_t;

struct node {
    business_t *business;
    node_t *next;
};

typedef struct list {
    node_t *head;
    node_t *tail;
} list_t;

/*
*   Function: make_LL
*   -----------------
*   Makes an empty linked list
*/
list_t*
make_LL (void) {
    list_t *list = malloc(sizeof(list_t));
    assert(list);
    list->head = list->tail = NULL;
    return list;
}

/*
*   Function: free_LL
*   -----------------
*   Traverses the linked list and frees memory
*/
void
free_LL (list_t *list) {
	node_t *curr, *prev;
	assert(list);
	curr = list->head;
	// NEED TO FREE MEMORY THAT THE BUSINESS PTR POINTS TO TOO
	while (curr) {
		prev = curr;
		curr = curr->next;
		free(prev);
	}
	free(list);
}

/*
*   Function: insert_business
*   -------------------------
*   Inserts a business into the top of the linked list
*/
list_t*
insert_business (list_t *list, business_t *business_data) {
	node_t *new = malloc(sizeof(node_t));
	assert(list && new);

	new->business = business_data;
	new->next = list->head;
	list->head = new;

	// Check if first insertion
	if (!(list->tail)) {
		list->tail = new;
	}
	return list;
}
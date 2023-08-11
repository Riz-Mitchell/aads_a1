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

	while (curr) {
		prev = curr;
		curr = curr->next;

		free_business(prev->business);
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

/*
*   Function: print_list
*   --------------------
*   Traverses through linked list and prints all values
*/
void
print_list(list_t *list) {
	node_t *curr;
	assert(list);

	curr = list->head;
	int n = 0;
	while (curr->business != NULL) {
		printf("\nCensus_year: %d\n", curr->business->census_year);
		printf("Block_id: %d\n", curr->business->block_id);
		printf("Property_id: %d\n", curr->business->property_id);
		printf("Base_property_id: %d\n", curr->business->base_property_id);
		printf("Building_address: %s\n", curr->business->building_address);
		printf("Clue_small_area: %s\n", curr->business->clue_small_area);
		printf("Business_address: %s\n", curr->business->business_address);
		printf("Trading_name: %s\n", curr->business->trading_name);
		printf("Industry_code: %d\n", curr->business->industry_code);
		printf("Industry_description: %s\n", curr->business->industry_description);
		printf("Seating_type: %s\n", curr->business->seating_type);
		printf("Number_of_seats: %d\n", curr->business->number_of_seats);
		printf("Longitude: %lf\n", curr->business->longitude);
		printf("Latitude: %lf\n", curr->business->latitude);
		printf("\n\n\n%d\n\n\n", n);
		n++;
		curr = curr->next;
	}
}
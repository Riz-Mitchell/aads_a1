#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "utils.h"

typedef struct node node_t;

struct node {
    business_t business;
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

		free_business(prev);
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
insert_business (list_t *list, node_t *business_node) {
	assert(list && business_node);

	business_node->next = list->head;
	list->head = business_node;

	// Check if first insertion
	if (!(list->tail)) {
		list->tail = business_node;
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
	while (curr != NULL) {
		printf("\nCensus_year: %d\n", curr->business.census_year);
		printf("Block_id: %d\n", curr->business.block_id);
		printf("Property_id: %d\n", curr->business.property_id);
		printf("Base_property_id: %d\n", curr->business.base_property_id);
		printf("Building_address: %s\n", curr->business.building_address);
		printf("Clue_small_area: %s\n", curr->business.clue_small_area);
		printf("Business_address: %s\n", curr->business.business_address);
		printf("Trading_name: %s\n", curr->business.trading_name);
		printf("Industry_code: %d\n", curr->business.industry_code);
		printf("Industry_description: %s\n", curr->business.industry_description);
		printf("Seating_type: %s\n", curr->business.seating_type);
		printf("Number_of_seats: %d\n", curr->business.number_of_seats);
		printf("Longitude: %lf\n", curr->business.longitude);
		printf("Latitude: %lf\n", curr->business.latitude);
		curr = curr->next;
	}
}

/*
*   Function: insert_field
*   ------------------------
*   Takes a field parsed from the csv and adds it to the business
*/
node_t*
insert_field (char *field, int field_num, node_t *business_node) {

    switch (field_num) {
        // Integer type insertions:
        case 1:
            business_node->business.census_year = convert_int(field);
            printf("\n\nhere\n\n");
            break;
        case 2:
            business_node->business.block_id = convert_int(field);
            break;
        case 3:
            business_node->business.property_id = convert_int(field);
            break;
        case 4:
            business_node->business.base_property_id = convert_int(field);
            break;
        
        // String type insertions:
        case 5:
            business_node->business.building_address = convert_string(field);
            break;
        case 6:
            business_node->business.clue_small_area = convert_string(field);
            break;
        case 7:
            business_node->business.business_address = convert_string(field);
            break;
        case 8:
            business_node->business.trading_name = convert_string(field);
            break;
        
        // Integer type insertion:
        case 9:
            business_node->business.industry_code = convert_int(field);
            break;

        // String type insertion:
        case 10:
            business_node->business.industry_description = convert_string(field);
            break;
        case 11:
            business_node->business.seating_type = convert_string(field);
            break;

        // Integer type insertion:
        case 12:
            business_node->business.number_of_seats = convert_int(field);
            break;
        
        // Double type insertion
        case 13:
            business_node->business.longitude = convert_double(field);
            break;
        case 14:
            business_node->business.latitude = convert_double(field);
            break;

    }
    return business_node;
}

/*
*   Function: free_business
*   ------------------------
*   Takes a business and frees the char pointers
*/
void
free_business (node_t *business_node) {
    free(business_node->business.building_address);
    free(business_node->business.clue_small_area);
    free(business_node->business.business_address);
    free(business_node->business.trading_name);
    free(business_node->business.industry_description);
    free(business_node->business.seating_type);
}
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "data.h"
#include "utils.h"
#include "list.h"

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

	while (curr != NULL) {
		prev = curr;
		curr = curr->next;

		free_strings(prev);
		free(prev);
	}
	free(list);
}

/*
*   Function: node_to_list
*   -------------------------
*   Inserts a business into the top of the linked list
*/
list_t*
node_to_list (list_t *list, node_t *curr_node) {
	assert(list && curr_node);

	curr_node->next = list->head;
	list->head = curr_node;

	// Check if first insertion
	if (!(list->tail)) {
		list->tail = curr_node;
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
    int condition = 1;
	curr = list->head;
	while (condition) {
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

        if (curr->next == NULL) {
            condition = 0;
        }
        else {
            curr = curr->next;
        }
	}
}

/*
*   Function: data_to_node
*   ------------------------
*   Takes a field parsed from the csv and adds it to the business
*/
node_t*
data_to_node (int field_num, char *field, node_t *curr_node) {

    switch (field_num) {
        // Integer type insertions:
        case 1:
            curr_node->business.census_year = convert_int(field);
            break;
        case 2:
            curr_node->business.block_id = convert_int(field);
            break;
        case 3:
            curr_node->business.property_id = convert_int(field);
            break;
        case 4:
            curr_node->business.base_property_id = convert_int(field);
            break;
        
        // String type insertions:
        case 5:
            curr_node->business.building_address = convert_string(field);
            break;
        case 6:
            curr_node->business.clue_small_area = convert_string(field);
            break;
        case 7:
            curr_node->business.business_address = convert_string(field);
            break;
        case 8:
            curr_node->business.trading_name = convert_string(field);
            break;
        
        // Integer type insertion:
        case 9:
            curr_node->business.industry_code = convert_int(field);
            break;

        // String type insertion:
        case 10:
            curr_node->business.industry_description = convert_string(field);
            break;
        case 11:
            curr_node->business.seating_type = convert_string(field);
            break;

        // Integer type insertion:
        case 12:
            curr_node->business.number_of_seats = convert_int(field);
            break;
        
        // Double type insertion
        case 13:
            curr_node->business.longitude = convert_double(field);
            break;
        case 14:
            curr_node->business.latitude = convert_double(field);
            break;

    }
    return curr_node;
}

/*
*   Function: free_business
*   -----------------------
*   Takes a business and frees the char pointers
*/
void
free_strings (node_t *curr_node) {
    free(curr_node->business.building_address);
    free(curr_node->business.clue_small_area);
    free(curr_node->business.business_address);
    free(curr_node->business.trading_name);
    free(curr_node->business.industry_description);
    free(curr_node->business.seating_type);
}

/*
*   Function: initialize_node
*   -------------------------
*   Takes a pointer to a node and initializes all values to prevent seg fault
*/
/*void
initialize_node(node_t *curr_node) {
    curr_node->business.census_year = 0;
    curr_node->business.block_id = 0;
    curr_node->business.property_id = 0;
    curr_node->business.base_property_id = 0;

    curr_node->businessbuilding_address = NULL;
    curr_node->business.clue_small_area = NULL;
    curr_node->business.business_address = NULL;
    curr_node->business.trading_name = NULL;

    curr_node->business.industry_code = 0;

    curr_node->business.industry_code = 0;

    curr_node->business.industry_description = NULL;
    curr_node->business.seating_type = NULL;
    curr_node->business.longitude = 0;
    curr_node->business.latitude = 0;
}*/
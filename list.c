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
*   ----------------------
*   Takes a node and list input and places the node
*   at the top of the linked list
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
*   Function: data_to_node
*   ------------------------
*   Takes data fields read in from a file and adds them
*   to their respective nodes
*
*   The function uses "field_num" to tell which field 
*   is being handled
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
*   Function: free_strings
*   ----------------------
*   Takes a node and free's the memory allocated for its
*   string fields
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
*   Function: list_search
*   ---------------------
*   Searches a list and prints business's with matching 
*   queries to "output_file" returns the number of 
*   matching queries
*/
int
list_search(list_t *list, char *query, FILE *output_file) {
    node_t *curr;
	assert(list);
    int num_matches = 0;
	curr = list->head;
	while (curr != NULL) {
        // Checks for query match and appends to output_file if found
        if (strcmp(query, curr->business.trading_name) == 0) {
            num_matches++;
            output_business(curr->business, output_file);
        }
        curr = curr->next;
	}
    return num_matches;
}

/*
*   Function: dataset_to_list
*   ----------------------
*   Reads data_file and inputs data into the linked list
*/
list_t*
dataset_to_list (FILE *data_file) {
    char line[MAX_LINE_LEN + 1];
    char *s;
    char *field;
    char *curr, *prev = NULL;

    int field_num;
    int first_line = 1;
    int just_compared = 0;

    list_t *list = make_LL();
    node_t *curr_node;

    while (fgets(line, MAX_LINE_LEN + 1, data_file)) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        curr_node = malloc(sizeof(node_t));
        assert(curr_node);
        
        s = line;
        field_num = 1;
        // Separate fields by ','
        while ((curr = strtok_r(s, ",", &s))) {
            // printf("\n\nField is %s\n\n", curr);
            if (prev != NULL) {
                if (compare_fields(prev, curr)) {
                    
                    field = link_fields(prev, curr);
                    just_compared = 1;
                }
                else {
                    field = curr;
                }
            }
            else {
                field = curr;
            }
            
            // Check to see if current field is meant to be added or not
            if (field[0] != '"') {
                data_to_node(field_num, field, curr_node);
                field_num++;
                prev = curr;

                if (just_compared) {
                    free(field);
                    just_compared = 0;
                }
            }
            else {
                prev = curr;
            }
            
        }
        node_to_list(list, curr_node);
    }
    return list;
}
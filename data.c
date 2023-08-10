#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data.h"

/*
*   Function: read_dataset
*   ----------------------
*   Reads data_file and inputs data into the linked list
*/
void
read_dataset (FILE *data_file) {
    char line[MAX_LINE_LEN + 1];        // Add space for null terminator
    int first_line = 1;
    business_t *curr_business;

    while (fgets(line, MAX_LINE_LEN + 1, data_file)) {

        if (first_line) {
                first_line = 0;
                continue;
        }
        curr_business = parse_line(line);
    }
    
}

/*
*   Function: parse_line
*   ------------------------
*   Takes a line from the csv file and inputs the data into the
*   linked list and returns a business_t variable
*/
business_t*
parse_line (char *line) {
    business_t *curr_business = malloc(sizeof(business_t));
    assert(curr_business);

    sscanf(line, "%d,%d,%d,%d,", curr_business->census_year,
                                 curr_business->block_id,
                                 curr_business->property_id,
                                 curr_business->base_property_id);
    return curr_business;
}
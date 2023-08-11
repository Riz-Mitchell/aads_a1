#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "list.h"
#include "data.h"
#include "utils.h"

/*
*   Function: read_dataset
*   ----------------------
*   Reads data_file and inputs data into the linked list
*/
void
read_dataset (FILE *data_file) {
    char field[MAX_FIELD_LEN + 1],
         ch;

    int first_line = 1,
        flag = 0,
        index = 0,
        field_num = 0;
    
    business_t *curr_business;
    list_t *list = make_LL();

    while ((ch = fgetc(data_file)) != EOF) {

        // Deal with file header
        if (ch != '\n' && first_line) {
            continue;
        } else first_line = 0;

        if (ch != '\n' && field_num == 0) {
            field_num++;
            curr_business = (business_t*)malloc(sizeof(business_t));
            assert(curr_business);
        }

        if (ch == '"') {
            flag = (flag + 1) % 2;
            continue;
        }

        if (!flag) {

            // If a newline is detected, that indicates current business to be inserted and new business to be allocated
            if (ch == '\n') {
                printf("\nnewline/n");
                field[index] = '\0';
                curr_business = insert_field(field, field_num, curr_business);
                list = insert_business(list, curr_business);

                field_num = 0;
                index = 0;  
            }

            // New field detected, index to be reset and prev field to be inserted into LL
            else if (ch == ',') {
                field[index] = '\0';
                curr_business = insert_field(field, field_num, curr_business);

                field_num++;
                index = 0;
            }
            else {
                field[index] = ch;
                index++;
            }
        }
        else {
            field[index] = ch;
            index++;
        }

    }

    // Final line insertion upon end of file
    /*field[index] = '\0';
    curr_business = insert_field(field, field_num, curr_business);
    list = insert_business(list, curr_business);*/
    print_list(list);
}

/*
*   Function: insert_field
*   ------------------------
*   Takes a field parsed from the csv and adds it to the business
*/
business_t*
insert_field (char *field, int field_num, business_t *curr_business) {

    switch (field_num) {
        // Integer type insertions:
        case 1:
            curr_business->census_year = convert_int(field);
            break;
        case 2:
            curr_business->block_id = convert_int(field);
            break;
        case 3:
            curr_business->property_id = convert_int(field);
            break;
        case 4:
            curr_business->base_property_id = convert_int(field);
            break;
        
        // String type insertions:
        case 5:
            curr_business->building_address = convert_string(field);
            break;
        case 6:
            curr_business->clue_small_area = convert_string(field);
            break;
        case 7:
            curr_business->business_address = convert_string(field);
            break;
        case 8:
            curr_business->trading_name = convert_string(field);
            break;
        
        // Integer type insertion:
        case 9:
            curr_business->industry_code = convert_int(field);
            break;

        // String type insertion:
        case 10:
            curr_business->industry_description = convert_string(field);
            break;
        case 11:
            curr_business->seating_type = convert_string(field);
            break;

        // Integer type insertion:
        case 12:
            curr_business->number_of_seats = convert_int(field);
            break;
        
        // Double type insertion
        case 13:
            curr_business->longitude = convert_double(field);
            break;
        case 14:
            curr_business->latitude = convert_double(field);
            break;

    }
    return curr_business;
}

/*
*   Function: free_business
*   ------------------------
*   Takes a business and frees the char pointers
*/
void
free_business (business_t *curr_business) {
    free(curr_business->building_address);
    free(curr_business->clue_small_area);
    free(curr_business->business_address);
    free(curr_business->trading_name);
    free(curr_business->industry_description);
    free(curr_business->seating_type);
}

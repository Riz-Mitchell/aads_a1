#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "data.h"
#include "utils.h"

/*
*   Function: read_dataset
*   ----------------------
*   Reads data_file and inputs data into the linked list
*/
void
read_dataset (FILE *data_file) {
    char field[MAX_LINE_LEN + 1], ch;        // Add space for null terminator
    int first_line = 1, flag = 0, index = 0, field_num = 1;
    business_t *curr_business;

    while ((ch = fgetc(data_file)) != EOF){
        if (ch == '"') {
            flag = (flag + 1) % 2;
            continue;
        }
        
        if (!flag) {
            if (ch == '\n') {
                field[index] = '\0';
                //printf("%s\n\n\nNew Line\n\n\n", field);
                field_num = 1;
                index = 0;
            }
            else if (ch == ',') {
                field[index] = '\0';
                //printf("%s\n\n", field);
                field_num++;
                index = 0;
                continue;
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
    
}

/*
*   Function: parse_line
*   ------------------------
*   Takes a line from the csv file and inputs the data into the
*   linked list and returns a business_t variable
*/
business_t*
insert_field (char *field, int field_num) {
    business_t *curr_business = malloc(sizeof(business_t));
    assert(curr_business);

    switch (field_num) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:

    }
    return curr_business;
}

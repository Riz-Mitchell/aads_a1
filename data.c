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
    char line[MAX_LINE_LEN + 1];
    char *s;
    char *field;
    char *curr, *prev = NULL;

    int field_num;
    int first_line = 1;

    list_t *list = make_LL();
    node_t *curr_node;

    while (fgets(line, MAX_LINE_LEN + 1, data_file)) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        curr_node = malloc(sizeof(node_t));
        assert(curr_node);
        //initialize_node(curr_node);
        s = line;
        field_num = 1;

        while ((curr = strtok_r(s, ",", &s))) {
            if (prev != NULL) {
                if (compare_fields(prev, curr)) {
                    field = link_fields(prev, curr);
                }
                else {
                    field = curr;
                }
            }
            else {
                field = curr;
            }
            
            // Check if a field needing to be linked is being tested or not
            if (field[0] != '"') {
                data_to_node(field_num, field, curr_node);
                printf("Field Number  %d is %s\n\n\n", field_num, field);
                field_num++;
                prev = curr;
            }
            else {
                prev = curr;
            }
            
        }
        node_to_list(list, curr_node);
    }
    free_LL(list);
}

/*
*   Function: compare_fields
*   ------------------------
*   Compares two prospective fields to check if they need to be linked
*/
int
compare_fields(char *prev, char *curr) {

    if (prev[0] == '"' && curr[strlen(curr) - 1] == '"') {
        return 1;       // Return 1 if fields are supposed to be linked
    }
    return 0;       // Returns 0 if fields are fine as is
}

/*
*   Function: link_fields
*   ------------------------
*   Links two fields if they both contained quotation marks at specified areas
*/
char*
link_fields(char *prev, char *curr) {
    // Get rid of the quotation marks and the \ characters
    prev += 1;
    curr[strlen(curr) - 1] = '\0';
    strcat(prev, curr);
    return prev;
}


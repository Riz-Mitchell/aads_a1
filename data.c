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

    int flag = 0,
        index = 0,
        field_num = 1,
        check_line = 0;
    int n = 0;

    list_t *list = make_LL();
    node_t *business_node;

    while ((ch = fgetc(data_file)) != EOF){

        if (check_line == 0) {
            if (ch == '\n') {
                check_line = 1;
            }
            continue;
        }

        if (check_ch(ch, flag)) {
            continue;
        }

        if (!flag) {
            if (ch == '\n') {
                field[index] = '\0';
                business_node = insert_field(field, field_num, business_node);  // Change to insert field into node
                list = insert_business(list, business_node);
                business_node = (node_t*)malloc(sizeof(node_t));
                printf("\n\nN is %d\n\n",n);
                n++;
                assert(business_node);

                field_num = 1;
                index = 0;
            }
            else if (ch == ',') {
                field[index] = '\0';
                business_node = insert_field(field, field_num, business_node);

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
    printf("\n\nyeye\n\n");
    // Final insertion
    print_list(list);
    printf("\n\nyeye\n\n");
    free_LL(list);
}


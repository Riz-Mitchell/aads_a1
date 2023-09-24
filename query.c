#include "query.h"

/*
*   Function: read_query
*   --------------------
*   Reads query from stdin and prints the number 
*   of matches in the dataset
*   
*   Also outputs further information about the 
*   query if found to a file with name specified
*   by the user
*/
void
read_query(list_t *list, FILE *output_file) {

    char *query = NULL;
    int num_matches;
    int n = 1;
    size_t query_size = 0;

    // Read lines of input from stdin
    while (getline(&query, &query_size, stdin) != -1) {
        if (n != 1) {
            fprintf(output_file, "\n");
        }

        // Remove the trailing newline if there is one
        remove_newline(query);

        fprintf(output_file, "%s", query);
        num_matches = list_search(list, query, output_file);
        if (num_matches) {
            printf("%s --> %d\n", query, num_matches);
        }
        else {
            printf("%s --> NOTFOUND\n", query);
        }
        n++;
    }
    free(query);
}

void
read_query_stage_two(dynamicArray_t *dynArray, FILE *output_file) {
    char *query = NULL;
    int s_comp = 0, c_comp = 0;
    int n = 1;
    size_t query_size = 0;

    // Read lines of input from stdin
    while (getline(&query, &query_size, stdin) != -1) {
        if (n != 1) {
            fprintf(output_file, "\n");
        }

        // Remove the trailing newline if there is one
        remove_newline(query);

        fprintf(output_file, "%s", query);
        binary_search(dynArray, query, output_file, &s_comp, &c_comp);

        int b_comp = c_comp * 8;
        printf("%s --> b%d c%d s%d\n", query, b_comp, c_comp, s_comp);
        n++;
        b_comp = c_comp = s_comp = 0;
    }
    free(query);
}

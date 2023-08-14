#include <stdio.h>
#include "query.h"

void
read_query(list_t *list, FILE *output_file) {
    char *query = NULL;
    int num_matches;
    size_t query_size = 0;
    int n = 1;

    while (getline(&query, &query_size, stdin) != -1) {
        if (n != 1) {
            fprintf(output_file, "\n");
        }

        // Remove the trailing newline if there is one
        remove_newline(query);

        fprintf(output_file, "%s\n", query);
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
#include "stages.h"

/*
*   Function: stage_one
*   -------------------
*   This function a dataset, reads it and adds
*   the data into a linked list
*/
void
stage_one(FILE *dataset, FILE *output_file) {
    list_t* list = dataset_to_list(dataset);

    read_query(list, output_file);

    free_LL(list);
}
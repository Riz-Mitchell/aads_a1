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

void
stage_two(FILE *dataset, FILE *output_file) {

    dynamicArray_t *dynArray = dataset_to_dynamic_array(dataset);

    /*fprintf(output_file, "Before sorting:");
    print_array(dynArray, output_file);
    fprintf(output_file, "\n");*/
    
    quicksort(dynArray, 0, dynArray->size - 1);

    read_query_stage_two(dynArray, output_file);

    /*fprintf(output_file, "\nAfter sorting:");
    print_array(dynArray, output_file);*/


    
    free_array(dynArray);
}
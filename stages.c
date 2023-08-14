#include "stages.h"

void
stage_one(FILE *dataset, FILE *output_file) {
    list_t* list = dataset_to_list(dataset);

    read_query(list, output_file);

    free_LL(list);
}
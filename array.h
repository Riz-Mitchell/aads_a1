#include "data.h"
#include "arrayds.h"
#include "quicksort.h"
#include <stdlib.h>

#define INITIAL_SIZE 50

#ifndef _ARRAY_H_
#define _ARRAY_H_

dynamicArray_t* create_array();
void free_array(dynamicArray_t *dynArray);
dynamicArray_t* dataset_to_dynamic_array (FILE *data_file);
void parse_line (char line[], dynamicArray_t *dynArray);
void field_to_array(char* field, dynamicArray_t *dynArray, int field_num);
void print_array (dynamicArray_t *dynArray, FILE *output_file);

#endif
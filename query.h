#include "list.h"
#include "arrayds.h"
#include "binarysearch.h"
#include <stdio.h>

#ifndef _QUERY_H_
#define _QUERY_H_

void read_query(list_t *list, FILE *output_file);
void read_query_stage_two(dynamicArray_t *dynArray, FILE *output_file);

#endif
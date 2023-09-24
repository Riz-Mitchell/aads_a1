#include "array.h"

#ifndef _BINARYSEARCH_H_
#define _BINARYSEARCH_H_

int binary_search (dynamicArray_t *dynArray, char *prefix, FILE *output_file, int *s_comp, int *c_comp);
int check_prefix(char *prefix, char *str, int *s_comp, int *c_comp);

#endif
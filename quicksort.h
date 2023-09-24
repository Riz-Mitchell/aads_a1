#include "arrayds.h"
#include "data.h"

#ifndef _QUICKSORT_H_
#define _QUICKSORT_H_

void swap (dynamicArray_t *dynArray, int i, int j);
int partition (dynamicArray_t *dynArray, int low, int high);
void quicksort (dynamicArray_t *dynArray, int low, int high);

#endif
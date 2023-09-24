#include "quicksort.h"

/**
 * Function: swap
 * -------------
 * Swaps the locations of 2 businesses in the dynamic array
*/
void
swap (dynamicArray_t *dynArray, int i, int j) {
    business_t temp = dynArray->array[i];
    dynArray->array[i] = dynArray->array[j];
    dynArray->array[j] = temp;
}

/**
 * Function: partition
 * -------------------
 * Partitions the array
*/
int
partition (dynamicArray_t *dynArray, int low, int high) {
    business_t pivot = dynArray->array[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        // Compare on trading names
        if (strcmp(dynArray->array[j].trading_name, pivot.trading_name) < 0) {
            i++;
            swap(dynArray, i, j);
        }
    }
    swap(dynArray, i + 1, high);
    return (i + 1);
}

/**
 * Function: quicksort
 * -------------------
 * Quick sort function to sort the dynamic array based on the trading names
*/
void
quicksort (dynamicArray_t *dynArray, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(dynArray, low, high);

        // Sort the sub arrays
        quicksort(dynArray, low, pivotIndex - 1);
        quicksort(dynArray, pivotIndex + 1, high);
    }
}
#include "binarysearch.h"

/*
// Binary Search in C

#include <stdio.h>

int binarySearch(int array[], int x, int low, int high) {
  // Repeat until the pointers low and high meet each other
  while (left <= right) {
        int mid = left + (right - left) / 2;
        int cmp = strcmp(arr[mid], target);

        if (cmp == 0) {
            return mid; // Found the target string at index mid
        } else if (cmp < 0) {
            left = mid + 1; // Target is in the right half
        } else {
            right = mid - 1; // Target is in the left half
        }
    }


  return -1;
}
*/

/**
 * Function: binary_search
 * -----------------------
 * Finds matching prefixes and and returns either true (1) or false (0) depending on if
 * matches were found or not found
*/
int
binary_search (dynamicArray_t *dynArray, char *prefix, FILE *output_file, int *s_comp, int *c_comp) {
    int low = 0;
    int high = dynArray->size - 1;
    int cond;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        char *mid_str = dynArray->array[mid].trading_name;
        cond = check_prefix(prefix, mid_str, s_comp, c_comp);

        if (cond == 0) {
            /**
             * ISSUE SEGFAULT IS OCCURING HERE. WITH SMALLER DATASET SIZES THE INDEX IS WRONG
             * USING DATASET_2 AT THIS POINT IN THE CODE MID = 1 THUS WOULD BE 2 IN THE COMING FOR LOOP
             * WHICH LIES OUTSIDE THE ARRAY RANGE
            */
            // Complete linear search in each direction until no prefix match is found
            output_business(dynArray->array[mid], output_file);
            for (int i = mid + 1; i < dynArray->size; i++) {
                // add prefix matches
                // print outputs to file
                if (check_prefix(prefix, dynArray->array[i].trading_name, s_comp, c_comp) == 0) {
                    output_business(dynArray->array[i], output_file);
                }
                else {
                    break;
                }
                
            }
            for (int i = mid - 1; i > 0; i--) {
                // add prefix matches
                if (check_prefix(prefix, dynArray->array[i].trading_name, s_comp, c_comp) == 0) {
                    output_business(dynArray->array[i], output_file);
                }
                else {
                    break;
                }
            }
            return 1;
        }
        else if (cond < 0) {
            high = mid -1;      // Go down
        }
        else {
            low = mid + 1;      // Go up
        }
    }
    return 0;
}

/**
 * Function: check_prefix
 * ----------------------
 * Returns 0 if prefix is a prefix to the string, 1 if the binary search needs to go up
 * and -1 if the binary search needs to go down
*/

int
check_prefix(char *prefix, char *str, int *s_comp, int *c_comp) {
    int match = 0;

    for (int i = 0; prefix[i] != '\0' || str[i] != '\0'; i++) {
        (*c_comp)++;
        if (prefix[i] == str[i]) {
            match = 0;
            if (i + 1 == strlen(prefix)) {
                (*s_comp)++;
                return match;
            }
        }
        else if (prefix[i] < str[i]) {
            match = -1;
            break;
        }
        else {
            match = 1;
            break;
        }
    }
    (*s_comp)++;
    return match;
}
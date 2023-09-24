#include "data.h"

#ifndef _ARRAYDS_H_
#define _ARRAYDS_H_

struct dynamicArray {
    int capacity;           // Max number of elements in the array
    int size;               // Current size of the array
    business_t *array;      // Pointer to array
};
typedef struct dynamicArray dynamicArray_t;

#endif
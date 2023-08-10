#include <stdio.h>
#include "stages.h"
#include "data.h"

void
stage_one(FILE *dataset) {
    read_dataset(dataset);
}
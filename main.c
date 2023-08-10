#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"
#include "data.h"

int
main (int argc, char *argv[]) {
    printf("argv[1] is %s and argv[2] is %s\n", argv[1], argv[2]);
    
    int stage_num = atoi(argv[1]);
    FILE *data_file = fopen(argv[2], "r");
    FILE *output_file = fopen(argv[3], "w");
    assert(data_file && output_file);
    printf("\n%d\n", stage_num);
    if (stage_num == 1) {
        read_dataset(data_file);
    }
    fclose(data_file);
    fclose(output_file);
    return 0;
}
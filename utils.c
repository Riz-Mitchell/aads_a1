#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "utils.h"

char*
convert_string(char *field) {
    char *new_field = strdup(field);
    return new_field;
}

int
convert_int(char *field) {
    int new_field = atoi(field);
    return new_field;
}

double
convert_double(char *field) {
    double new_field = atof(field);
    return new_field;
}
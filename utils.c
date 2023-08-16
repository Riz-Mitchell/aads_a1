#include "utils.h"

/*
*   Function: convert_string
*   ------------------------
*   Converts string to space efficient string
*/
char*
convert_string(char *field) {
    char *new_field = strdup(field);
    return new_field;
}

/*
*   Function: convert_int
*   ---------------------
*   Converts string to int
*/
int
convert_int(char *field) {
    int new_field = atoi(field);
    return new_field;
}

/*
*   Function: convert_double
*   -----------------------
*   Converts string to double
*/
double
convert_double(char *field) {
    double new_field = atof(field);
    return new_field;
}
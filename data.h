#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#ifndef _DATA_H_
#define _DATA_H_

#define MAX_LINE_LEN 512
#define MAX_FIELD_LEN 128

struct business {
    int census_year;
    int block_id;
    int property_id;
    int base_property_id;
    char *building_address;
    char *clue_small_area;
    char *business_address;
    char *trading_name;
    int industry_code;
    char *industry_description;
    char *seating_type;
    int number_of_seats;
    double longitude;
    double latitude;
};
typedef struct business business_t;

// Function definitions
int compare_fields(char *prev, char *curr);
char* link_fields(char *prev, char *curr);
void output_business(business_t curr_business, FILE* output_file);
char* str_append(char* prev, char* curr);
void remove_newline(char *query);

#endif
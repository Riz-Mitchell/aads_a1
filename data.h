#include <stdio.h>

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
void read_dataset (FILE *data_file);

#endif
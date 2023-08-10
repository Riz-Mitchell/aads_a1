#ifndef _DATA_H_
#define _DATA_H_

#define MAX_LINE_LEN 512
#define MAX_FIELD_LEN 128

struct business {
    int census_year;
    int block_id;
    int property_id;
    int base_property_id;
    char building_address[MAX_FIELD_LEN + 1];
    char clue_small_area[MAX_FIELD_LEN + 1];
    char business_address[MAX_FIELD_LEN + 1];
    char trading_name[MAX_FIELD_LEN + 1];
    int industry_code;
    char industry_description[MAX_FIELD_LEN + 1];
    char seating_type[MAX_FIELD_LEN + 1];
    int number_of_seats;
    double longitude;
    double latitude;
};
typedef struct business business_t;

// Function definitions
void read_dataset (FILE *data_file);
#endif
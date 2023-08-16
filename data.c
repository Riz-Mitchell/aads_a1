#include "data.h"

/*
*   Function: compare_fields
*   ------------------------
*   Compares two prospective fields to check if they need to be linked
*/
int
compare_fields(char *prev, char *curr) {

    if (prev[0] == '"' && curr[strlen(curr) - 1] == '"') {
        return 1;       // Return 1 if fields are supposed to be linked
    }
    return 0;       // Returns 0 if fields are fine as is
}

/*
*   Function: link_fields
*   ------------------------
*   Links two fields if they both contained quotation marks at specified areas
*/
char*
link_fields(char *prev, char *curr) {
    // Get rid of the quotation marks and the \ characters
    prev += 1;
    curr[strlen(curr) - 1] = '\0';
    printf("prev is %s\ncurr is %s\n", prev, curr);


    return str_append(prev, curr);
}

/*
*   Function: output_business
*   ------------------------
*   Prints a business to the output file
*/
void
output_business(business_t curr_business, FILE* output_file) {
    fprintf(output_file, "\n--> census_year: %d || ", curr_business.census_year);
    fprintf(output_file, "block_id: %d || ", curr_business.block_id);
    fprintf(output_file, "property_id: %d || ", curr_business.property_id);
    fprintf(output_file, "base_property_id: %d || ", curr_business.base_property_id);
    fprintf(output_file, "building_address: %s || ", curr_business.building_address);
    fprintf(output_file, "clue_small_area: %s || ", curr_business.clue_small_area);
    fprintf(output_file, "business_address: %s || ", curr_business.business_address);
    fprintf(output_file, "trading_name: %s || ", curr_business.trading_name);
    fprintf(output_file, "industry_code: %d || ", curr_business.industry_code);
    fprintf(output_file, "industry_description: %s || ", curr_business.industry_description);
    fprintf(output_file, "seating_type: %s || ", curr_business.seating_type);
    fprintf(output_file, "number_of_seats: %d || ", curr_business.number_of_seats);
    fprintf(output_file, "longitude: %.5lf || ", curr_business.longitude);
    fprintf(output_file, "latitude: %.5lf || ", curr_business.latitude);
}

char*
str_append(char* prev, char* curr) {
    int index = 0;
    char buffer[MAX_FIELD_LEN * 2 + 1];
    char *new;
    
    for (int i = 0; prev[i] != '\0'; i++) {
        buffer[index] = prev[i];
        index++;
    }

    // Account for comma removed when tokenizing
    buffer[index] = ',';
    index++;

    for (int i = 0; curr[i] != '\0'; i++) {
        buffer[index] = curr[i];
        index++;
    }
    buffer[index] = '\0';
    printf("Buffer is %s", buffer);
    new = strdup(buffer);
    return new;
}

void
remove_newline(char *query) {
    int len = strlen(query);
    if (len > 0 && query[len - 1] == '\n') query[len - 1] = '\0';
}
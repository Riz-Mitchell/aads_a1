#include "array.h"

/**
 * Function: create_array
 * ---------------------
 * Allocates memory for a dynamic array and returns a pointer to that array
*/
dynamicArray_t*
create_array() {
    dynamicArray_t *dynArray = malloc(sizeof(dynamicArray_t));
    assert(dynArray);

    dynArray->capacity = INITIAL_SIZE;
    dynArray->size = 0;
    dynArray->array = (business_t*)malloc(sizeof(business_t) * INITIAL_SIZE);
    assert(dynArray->array);
    return dynArray;
}

void
free_array(dynamicArray_t *dynArray) {
    
    for (int i = 0; i < (dynArray->size); i++) {
        free(dynArray->array[i].building_address);
        free(dynArray->array[i].clue_small_area);
        free(dynArray->array[i].business_address);
        free(dynArray->array[i].trading_name);
        free(dynArray->array[i].industry_description);
        free(dynArray->array[i].seating_type);
    }
    free(dynArray->array);
    free(dynArray);
}

/*
*   Function: dataset_to_list
*   ----------------------
*   Reads data_file and inputs data into the linked list
*/
dynamicArray_t*
dataset_to_dynamic_array (FILE *data_file) {
    char line[MAX_LINE_LEN + 1];
    int first_line = 1;

    dynamicArray_t *dynArray = create_array();

    while (fgets(line, MAX_LINE_LEN + 1, data_file)) {
        // Skip file header
        if (dynArray->size == dynArray->capacity && dynArray != NULL) {
            int new_capacity = dynArray->capacity * 2;
            business_t *newArray = realloc(dynArray->array, new_capacity * sizeof(business_t));
            assert(newArray);
            dynArray->array = newArray;
            dynArray->capacity = new_capacity;
        }
        if (first_line) {
            first_line = 0;
            continue;
        }
        parse_line(line, dynArray);
        dynArray->size++;
    }
    // Sort the array
    //printf("\n\ndynArray has %d elements\n\n", dynArray->size);
    return dynArray;
}

/**
 * Function: parse_line
 * --------------------
 * This function parses a line, extracts the fields, and then inserts them into a business in
 * the dynamic array
 * 
*/
void
parse_line (char line[], dynamicArray_t *dynArray) {

    char *s = line;
    char *field;
    char *curr, *prev = NULL;
    int just_compared = 0;
    int field_num = 1;

    // Separate fields by ','
    while ((curr = strtok_r(s, ",", &s))) {
        // printf("\n\nField is %s\n\n", curr);
        if (prev != NULL) {
            if (compare_fields(prev, curr)) {
                field = link_fields(prev, curr);
                just_compared = 1;
            }
            else {
                field = curr;
            }
        }
        else {
            field = curr;
        }

        // Check to see if current field is meant to be added or not
        if (field[0] != '"') {
            // printf("%s, ", field);
            field_to_array(field, dynArray, field_num);
            field_num++;
            prev = curr;

            if (just_compared) {
                free(field);
                just_compared = 0;
            }
        }
        else
        {
            prev = curr;
        }
    }
}

/**
 * Function: field_to_array
 * ------------------------
 * Takes a field extracted from a line of the csv file and inserts it into the array
 * 
*/
void
field_to_array(char* field, dynamicArray_t *dynArray, int field_num) {
    int index = dynArray->size;

    switch (field_num) {
        // Int type insertions:
        case 1:
            dynArray->array[index].census_year = convert_int(field);
            break;
        case 2:
            dynArray->array[index].block_id = convert_int(field);
            break;
        case 3:
            dynArray->array[index].property_id = convert_int(field);
            break;
        case 4:
            dynArray->array[index].base_property_id = convert_int(field);
            break;
        
        // String type insertions:
        case 5:
            dynArray->array[index].building_address = convert_string(field);
            break;
        case 6:
            dynArray->array[index].clue_small_area = convert_string(field);
            break;
        case 7:
            dynArray->array[index].business_address = convert_string(field);
            break;
        case 8:
            dynArray->array[index].trading_name = convert_string(field);
            break;
        
        // Integer type insertion:
        case 9:
            dynArray->array[index].industry_code = convert_int(field);
            break;

        // String type insertion:
        case 10:
            dynArray->array[index].industry_description = convert_string(field);
            break;
        case 11:
            dynArray->array[index].seating_type = convert_string(field);
            break;

        // Integer type insertion:
        case 12:
            dynArray->array[index].number_of_seats = convert_int(field);
            break;
        
        // Double type insertion
        case 13:
            dynArray->array[index].longitude = convert_double(field);
            break;
        case 14:
            dynArray->array[index].latitude = convert_double(field);
            break;
    }
}

void
print_array (dynamicArray_t *dynArray, FILE *output_file) {
    int size = dynArray->size;
    for (int i = 0; i < size; i++) {
        fprintf(output_file, "\n--> census_year: %d || ", dynArray->array[i].census_year);
        fprintf(output_file, "block_id: %d || ", dynArray->array[i].block_id);
        fprintf(output_file, "property_id: %d || ", dynArray->array[i].property_id);
        fprintf(output_file, "base_property_id: %d || ", dynArray->array[i].base_property_id);
        fprintf(output_file, "building_address: %s || ", dynArray->array[i].building_address);
        fprintf(output_file, "clue_small_area: %s || ", dynArray->array[i].clue_small_area);
        fprintf(output_file, "business_address: %s || ", dynArray->array[i].business_address);
        fprintf(output_file, "trading_name: %s || ", dynArray->array[i].trading_name);
        fprintf(output_file, "industry_code: %d || ", dynArray->array[i].industry_code);
        fprintf(output_file, "industry_description: %s || ", dynArray->array[i].industry_description);
        fprintf(output_file, "seating_type: %s || ", dynArray->array[i].seating_type);
        fprintf(output_file, "number_of_seats: %d || ", dynArray->array[i].number_of_seats);
        fprintf(output_file, "longitude: %.5lf || ", dynArray->array[i].longitude);
        fprintf(output_file, "latitude: %.5lf || ", dynArray->array[i].latitude);
    }
}


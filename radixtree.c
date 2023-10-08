#include "radixtree.h"



/**
 * Function: create_tree
 * Creates a radix tree
*/
tree_t*
create_tree() {
    tree_t *new_tree = malloc(sizeof(tree_t));
    assert(new_tree);

    new_tree->root = NULL;
    return new_tree;
}

/**
 * Function: free_tree
 * -------------------
 * Frees all data associated with the input root
*/
void
free_tree(branch_t *root) {
    if (root == NULL) {
        return;
    }

    free_tree(root->branchA);
    free_tree(root->branchB);

    free(root->data.building_address);
    free(root->data.clue_small_area);
    free(root->data.business_address);
    free(root->data.trading_name);
    free(root->data.industry_description);
    free(root->data.seating_type);
    free(root->prefix);
    free(root);
}

/**
 * Function: data_to_tree
 * ----------------------
 * Inserts the data from "data_file" into the radix tree
*/
tree_t*
data_to_tree(FILE *data_file, tree_t *tree, FILE *output_file) {
    char line[MAX_LINE_LEN + 1];
    char *s;
    char *field;
    char *curr, *prev = NULL;

    int field_num;
    int first_line = 1;
    int just_compared = 0;

    branch_t *curr_branch;

    while (fgets(line, MAX_LINE_LEN + 1, data_file)) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        printf("\n\n\nhello\n\n\n");
        curr_branch = malloc(sizeof(branch_t));
        printf("\n\n\nnoooooo\n\n\n");
        assert(curr_branch);
        
        s = line;
        field_num = 1;
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
                data_to_branch(field_num, field, curr_branch);
                field_num++;
                prev = curr;

                if (just_compared) {
                    free(field);
                    just_compared = 0;
                }
            }
            else {
                prev = curr;
            }
            
        }
        curr_branch->prefix = string_to_binary(curr_branch->data.trading_name);
        curr_branch->prefix_bits = strlen(curr_branch->prefix);
        fprintf(output_file, "\nTrading name in binary is: %s and is %d bits long", curr_branch->prefix, curr_branch->prefix_bits);
        output_business(curr_branch->data, output_file);
        curr_branch->branchA = NULL;
        curr_branch->branchB = NULL;
        tree = insert_branch(tree, curr_branch);
    }
    return tree;
}

void
data_to_branch(int field_num, char *field, branch_t *curr_branch) {
    switch (field_num) {
        // Integer type insertions:
        case 1:
            curr_branch->data.census_year = convert_int(field);
            break;
        case 2:
            curr_branch->data.block_id = convert_int(field);
            break;
        case 3:
            curr_branch->data.property_id = convert_int(field);
            break;
        case 4:
            curr_branch->data.base_property_id = convert_int(field);
            break;
        
        // String type insertions:
        case 5:
            curr_branch->data.building_address = convert_string(field);
            break;
        case 6:
            curr_branch->data.clue_small_area = convert_string(field);
            break;
        case 7:
            curr_branch->data.business_address = convert_string(field);
            break;
        case 8:
            curr_branch->data.trading_name = convert_string(field);
            break;
        
        // Integer type insertion:
        case 9:
            curr_branch->data.industry_code = convert_int(field);
            break;

        // String type insertion:
        case 10:
            curr_branch->data.industry_description = convert_string(field);
            break;
        case 11:
            curr_branch->data.seating_type = convert_string(field);
            break;

        // Integer type insertion:
        case 12:
            curr_branch->data.number_of_seats = convert_int(field);
            break;
        
        // Double type insertion
        case 13:
            curr_branch->data.longitude = convert_double(field);
            break;
        case 14:
            curr_branch->data.latitude = convert_double(field);
            break;

    }
}

/**
 * Function: insert_branch
 * ---------------------
 * Takes a tree and branch as input and inserts the branch into the tree
*/
tree_t*
insert_branch(tree_t *tree, branch_t *inserting) {
    branch_t *curr = tree->root, *prev = NULL;
    int result, cond = 0;;
    // First insertion
    if (curr == NULL) {
        curr = inserting;
    }
    else {
        while (1) {
            result = compare_prefix(curr->prefix, inserting->prefix);
            if (result == 0) {
                /* Insert duplicate case */
                break;
            }
            else if (result == 1) {
                // split root branch and break loop
                if (curr == tree->root) {cond = 1;}
                branch_t *new = split_branches(curr, inserting);
                if (cond) {
                    tree->root = new;
                }
                else {
                    // Determine new branch's parent and attatch it
                    if (new->prefix[0] == '0') {
                        prev->branchA = new;
                    }
                    else {
                        prev->branchB = new; 
                    }
                }
                cond = 0;
                break;
            }
            else {
                // remove bits prefix from inserting
                inserting->prefix = remove_bits(inserting->prefix, curr->prefix_bits);
                inserting->prefix_bits = strlen(inserting->prefix);
                // Take branch A
                if (inserting->prefix[0] == 0) {
                    // If NULL place branch
                    if (curr->branchA == NULL) {
                        curr->branchA = inserting;      // Inserted
                        break;
                    }
                    // Else traverse
                    else {
                        prev = curr;
                        curr = curr->branchA;
                    }
                }
                // Take branch B
                else {
                    if (curr->branchB == NULL) {
                        // If NULL place
                        if (curr->branchB == NULL) {
                            curr->branchB = inserting;
                            break;
                        }
                        // Else traverse
                        else {
                            prev = curr;
                            curr = curr->branchB;
                        }
                    }
                }
            }
        }
    }
    return tree;
}

/**
 * Function: compare_prefix
 * ------------------------
 * Compares the 2 strings and returns 0 if the strings are the same 1 if they differ at any point
 * and need to be split or -1 if curr_prefix is a substring of insert_prefix and we need to
 * keep going down the tree
*/
int
compare_prefix(char *curr_prefix, char *insert_prefix) {
    // check if equal
    if (strcmp(curr_prefix, insert_prefix) == 0) {
        // duplicate case
        return 0;
    }
    
    for (int i = 0; curr_prefix[i] != '\0' && insert_prefix[i] != '\0'; i++) {
        if (curr_prefix[i] != insert_prefix[i]) {
            printf("at i = %d curr[i] = %c and insert[i] = %c\n\n", i, curr_prefix[i], insert_prefix[i]);
            printf("split in loop");
            return 1;
        }
    }
    // If insert is equal but a substring of curr
    if (strlen(curr_prefix) > strlen(insert_prefix)) {
        printf("split out loop");
        return 1;
    }
    printf("traverse");
    return -1;
}

branch_t*
split_branches(branch_t *curr, branch_t *inserting) {
    branch_t *new = malloc(sizeof(branch_t));
    new->prefix = get_common_prefix(curr->prefix, inserting->prefix);
    new->prefix_bits = strlen(new->prefix);

    /* CHANGE REMAINING PREFIX IN THE "CURR" AND "INSERTING" branchS  m */
    curr->prefix = remove_bits(curr->prefix, new->prefix_bits);
    inserting->prefix = remove_bits(inserting->prefix, new->prefix_bits);

    // Attatch the leaf branchs
    if (curr->prefix[0] == '0') {
        new->branchA = curr;
        new->branchB = inserting;
    }
    else {
        new->branchA = inserting;   // might need to check which leads where
        new->branchB = curr;
    }
    return new;
}

/**
 * Function: get_common_prefix
 * ---------------------------
 * This function returns the matching substring of the input prefixes
*/
char*
get_common_prefix(char *curr_prefix, char *insert_prefix) {
    int max_size = 50;
    int size = 0;
    char *output = malloc(sizeof(char) * max_size), *temp;
    assert(output);
    for (int i = 0; curr_prefix[i] != '\0' && insert_prefix[i] != '\0'; i++) {
        if (size < max_size) {
            if (curr_prefix[i] == insert_prefix[i]) {
                output[size] = curr_prefix[i];
                size++;
            }
            else {
                break;
            }
        }
        else {
            max_size *= 2;
            output = realloc(output, sizeof(char) * max_size);
            assert(output);
        }
    }
    output[size] = '\0';
    temp = malloc(sizeof(char) * size);
    strcpy(temp, output);
    free(output);
    return temp;
}

/**
 * Funbction: remove_bits
 * ----------------------
 * Removes "bits" bits from the prefix and returns the new string
*/
char*
remove_bits(char *prefix, int bits) {
    int len = strlen(prefix), index = 0;
    char *output = malloc(sizeof(char) * len), *temp;
    assert(output);
    for (int i = bits; i < len; i++) {
        output[index] = prefix[i];
        index++;
    }
    output[index] = '\0';
    temp = malloc(sizeof(char) * index);
    strcpy(temp, output);
    free(output);
    free(prefix);
    return output;
}

/**
 * Function: output_tree
 * --------------------- 
*/
void
output_tree(branch_t *root, FILE *output_file) {
    if (root->data.trading_name != NULL) {
        output_business(root->data, output_file);
        printf("\n\n\nyes\n\n\n");
    }
    if (root->branchA != NULL) {
        output_tree(root->branchA, output_file);
        printf("\n\n\nyes\n\n\n");
    }
    if (root->branchB != NULL) {
        output_tree(root->branchA, output_file);
        printf("\n\n\nyes\n\n\n");
    }
}
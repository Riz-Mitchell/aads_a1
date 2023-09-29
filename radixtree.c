#include "radixtree.h"

tree_t*
create_tree() {
    tree_t *new_tree = malloc(sizeof(tree_t));
    assert(new_tree);

    new_tree->root = NULL;
    return new_tree;
}

/**
 * Function: data_to_tree
 * ----------------------
*/
tree_t*
data_to_tree(FILE *data_file, tree_t *tree) {
    char line[MAX_LINE_LEN + 1];
    char *s;
    char *field;
    char *curr, *prev = NULL;

    int field_num;
    int first_line = 1;
    int just_compared = 0;

    node_t *curr_node;

    while (fgets(line, MAX_LINE_LEN + 1, data_file)) {
        if (first_line) {
            first_line = 0;
            continue;
        }
        curr_node = malloc(sizeof(node_t));
        assert(curr_node);
        
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
                data_to_node(field_num, field, curr_node);
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
        curr_node->prefix = string_to_binary(curr_node->data.trading_name);
        curr_node->prefix_bits = strlen(curr_node->prefix);
        curr_node->branchA = NULL;
        curr_node->branchB = NULL;
        insert_node(tree, curr_node);
    }
    return tree;
}

void
data_to_node(int field_num, char *field, node_t *curr_node) {
    switch (field_num) {
        // Integer type insertions:
        case 1:
            curr_node->data.census_year = convert_int(field);
            break;
        case 2:
            curr_node->data.block_id = convert_int(field);
            break;
        case 3:
            curr_node->data.property_id = convert_int(field);
            break;
        case 4:
            curr_node->data.base_property_id = convert_int(field);
            break;
        
        // String type insertions:
        case 5:
            curr_node->data.building_address = convert_string(field);
            break;
        case 6:
            curr_node->data.clue_small_area = convert_string(field);
            break;
        case 7:
            curr_node->data.business_address = convert_string(field);
            break;
        case 8:
            curr_node->data.trading_name = convert_string(field);
            break;
        
        // Integer type insertion:
        case 9:
            curr_node->data.industry_code = convert_int(field);
            break;

        // String type insertion:
        case 10:
            curr_node->data.industry_description = convert_string(field);
            break;
        case 11:
            curr_node->data.seating_type = convert_string(field);
            break;

        // Integer type insertion:
        case 12:
            curr_node->data.number_of_seats = convert_int(field);
            break;
        
        // Double type insertion
        case 13:
            curr_node->data.longitude = convert_double(field);
            break;
        case 14:
            curr_node->data.latitude = convert_double(field);
            break;

    }
    return curr_node;
}

/**
 * Function: insert_node
 * ---------------------
 * Takes a tree and node as input and inserts the node into the tree
*/
void
insert_node(tree_t *tree, node_t *inserting) {
    node_t *curr = tree->root, *prev = NULL;
    int result;
    // First insertion
    if (curr == NULL) {
        curr = inserting;
    }
    else {
        while (1) {
            result = compare_prefix(curr->prefix, insert_node);
            if (result == 0) {
                /* Insert duplicate case */
            }
            else if (result == 1) {
                split_nodes(curr, inserting, prev);
                /* Need to fix issues arising from if the root node is split and how
                /* to re-attatch the new root to the tree. */
                /* Maybe try passing through the tree itself? */
            }
            else {
                /* Keep traversing case */
                /* In this case the prefix bits in curr->prefix */
                /* must be removed from inserting->prefix */
                /* In the case that the branch path chosen to take is NULL we want
                /* to place the node with the remaining prefix there */
            }
            prev = curr;
            /* Decide next branch*/
        }
    }
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

void
split_nodes(node_t *curr, node_t *inserting, node_t *prev) {
    node_t *new = malloc(sizeof(node_t));
    new->prefix = get_common_prefix(curr->prefix, inserting->prefix);
    new->prefix_bits = strlen(new->prefix);

    /* CHANGE REMAINING PREFIX IN THE "CURR" AND "INSERTING" NODES  m */
    curr->prefix = remove_bits(curr->prefix, new->prefix_bits);
    inserting->prefix = remove_bits(inserting->prefix, new->prefix_bits);

    // Attatch the leaf nodes
    if (curr->prefix[0] == '0') {
        new->branchA = curr;
        new->branchB = inserting;
    }
    else {
        new->branchA = inserting;   // might need to check which leads where
        new->branchB = curr;
    }

    // Determine new node's parent and attatch it
    if (new->prefix[0] == '0') {
        prev->branchA = new;
    }
    else {
        prev->branchB = new; 
    }
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
                output[size] = curr_prefix;
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
    temp = output;
    output = strdup(temp);
    free(temp);
    return output;
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
    temp = output;
    output = strdup(temp);
    free(prefix);
    free(temp);
    return output;
}
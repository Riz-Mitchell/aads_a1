#include "binops.h"

/**
 * Function: char_to_binary
 * ------------------------
 * Takes a character and returns a string equal to the character converted
 * to an 8 bit bninary number
*/
char*
char_to_binary(char c) {

    char *bin_rep = malloc(9 * sizeof(char));
    assert(bin_rep);

    for (int j = 7; j >= 0; j--) {
        bin_rep[7 - j] = ((c >> j) & 1) ? '1' : '0';
    }

    bin_rep[8] = '\0'; // Null-terminate the binary string
    return bin_rep;
}

/**
 * Function: string_to_binary
 * --------------------------
 * Takes a string input and returns a string of bits equal to the original
 * string in bit form
*/
char*
string_to_binary(char *input) {
    
    // Iterate through each character in the input string
    char *output = malloc(((strlen(input) + 1) * 8 + 1) * sizeof(char));
    assert(output);
    int index = 0;

    for (int i = 0; input[i] != '\0'; i++) {
        char *bin_rep = char_to_binary(input[i]);
        for (int j = 0; j < 8; j++) {
            output[index] = bin_rep[j];
            index++;
        }
        free(bin_rep);
    }
    
    for (int i = 0; i < 8; i++) {
        output[index] = '0';
        index++;
    }
    output[index] = '\0';
    return output;
}
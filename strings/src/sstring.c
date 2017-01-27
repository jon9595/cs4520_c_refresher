#include <string.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../include/sstring.h"

bool string_valid(const char *str, const size_t length) {

    if(str == NULL) { //checking for bad input
        return false;
    }

    if(length <= 0) { //checking for a negative or zero length
        return false;
    }

    const char end = str[length - 1]; //grabbing the last char of the input str

    if(strcmp(&end, "\0") == 0) { //comparing the last character of the string to the null terminator
        return true;
    }
    else { //if we get here, that means the string did not end in the null terminator
        return false;
    }
}

char *string_duplicate(const char *str, const size_t length) {

    if(str == NULL) { //checking for bad input
        return NULL;
    }

    if(length <= 0) { //checking for 0 or negative length
        return NULL;
    }

    char* str_cpy = NULL; //initializing the new string to NULL
    str_cpy = (char*) malloc(sizeof(char) * length); //getting memory allocated for our new string

    if(str_cpy == NULL) { //checking to make sure we were allocated memory
        return NULL;
    }

    memcpy(str_cpy, str, sizeof(char) * length); //copying the input string into the new string

    return str_cpy;

}

bool string_equal(const char *str_a, const char *str_b, const size_t length) {

    if(str_a == NULL || str_b == NULL) { //checking for bad input strings
        return false;
    }

    if(length <= 0) { //checking for 0 and negative length
        return false;
    }

    if(strcmp(str_a, str_b) == 0) { //if the two strings contain the same chars, strcmp returns 0
        return true;
    }
    else { //getting to this means the strings were not equal
        return false;
    }
}

int string_length(const char *str, const size_t length) {

    if(str == NULL) { //checking for a bad input string
        return -1;
    }

    if(length <= 0) { //checking for invaild length
        return -1;
    }

    int result_return = 0; //creating the return variable

    result_return = strlen(str);

    if(result_return <= length) { //if the results are within the allowed string length, we return the total length
        return result_return;
    }
    else { //bigger string than allowed
        return -1;
    }
}

/* The function string_tokenize takes in a string, str, that is delimited by different chars that are represented in the delims array.
 * The different paramaters give the length of the string and the total expected tokens as well as the maximum token length. Also,
 * an array of strings called tokens is passed to store the parsed tokens. This function utilizies the library function strtok, which
 * breaks apart the input string based on the array of delims. In order to use strtok, I had to copy the input string which is of type
 * const char*, and copy it into a stringof time char*. This is due to the fact that strtok parses the tokens in place, and const is
 * unable to be parsed in this manner.
 */
int string_tokenize(const char *str, const char *delims, const size_t str_length,char **tokens, const size_t max_token_length, const size_t requested_tokens) {

    if(str == NULL || delims == NULL || tokens == NULL) { //checking for bad inputs
        return 0;
    }

    if(str_length <= 0 || max_token_length <= 0 || requested_tokens <= 0) { //checking for 0 and negative values
        return 0;
    }

    char copy_string[max_token_length]; //creating a non-constant string for the input string
    char* token_ptr; //this is the pointer to be used for the strtok function
    strcpy(copy_string, str); //putting the const string into a non const string so we can use strtok

    token_ptr = strtok(copy_string, delims); //the first time strtok runs, you must pass the string to tokenize in, then a NULL pointer 
    //is passed on each successive call. This is beacuse the strings position is stored by the function
    int i = 0;
    for(i = 0; i < requested_tokens; i++) { 
        if(token_ptr == NULL) { //token_ptr will become NULL when strtok is done tokenizing the input string
            break; //get out of the loop so we can return the number of tokens
        }

        if(tokens[i] != NULL) { //ensuring the tokens array as been initialized correctly
            if(token_ptr != NULL) { //this is a second check for a NULL token_ptr, in case the strtok returned NULL and we didn't catch it
                strcpy(tokens[i], token_ptr); //copying the string into the memory in the tokens array
            }
            else { //if we get here, we won't attempt to store the token at the location in the tokens array, or else we get a segfault
                break;
            }
        }
        else { //getting to this else statement means the tokens array[i] was not allocated correctly
            return -1;
        }

        token_ptr = strtok(NULL, delims); //continuing to tokenize the string. NOTE: now a null pointer is passed because strtok
        //already contains a reference to copy_string
    }

    return i; //if we make it here, i represents the total number of tokens parsed and stored in the tokens array
}

bool string_to_int(const char *str, int *converted_value) {

    if(str == NULL || converted_value == NULL) {
        return false;
    }

    char* letter = NULL;
    *converted_value = (int) strtol(str, &letter, 10);

    if(errno == 34) {
        *converted_value = 0;
        errno = 0; //clearing the out-of-bounds error message
        return false;
    }
    else if((strcmp(letter, "") == 0) || (strcmp(letter, " ") == 0)) { //comparing string to acceptable chars
        return true;
    }
    else {
        return true;
    }
}

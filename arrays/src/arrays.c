#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

bool array_copy(const void *src, void *dst, const size_t elem_size, const size_t elem_count) {

    if(src == NULL || dst == NULL) { //checking for a NULL source and destination arrays
        return false;
    }

    if(elem_size <= 0 || elem_count <= 0) { //checking to ensure the size of the inputs are non-negative
        return false;
    }

    memcpy(dst, src, elem_size * elem_count); //using memcpy to copy src into dst

    if(dst == NULL) { //this indicates the memcpy did notwork and we can return false
        return false;
    }
    else { //this indicates the memcpy did work, so return true
        return true;
    }
}

bool array_is_equal(const void *data_one, void *data_two, const size_t elem_size, const size_t elem_count) {

    if(data_one == NULL || data_two == NULL) { //checking for NULL source arrays
        return false;
    }

    if(elem_size <= 0 || elem_count <= 0) { //ensuring a non-negative count and size
        return false;
    }

    int compare = 0;

    compare = memcmp(data_one, data_two, elem_size * elem_count);

    if(compare == 0) { //memcmp returns 0 if the two arrays are equal so we can return true
        return true;
    }
    else { //memcpy did not return 0. The arrays are not equal.
        return false;
    }

}

ssize_t array_locate(const void *data, const void *target, const size_t elem_size, const size_t elem_count) {

    if(data == NULL || target == NULL) { //checking for bad input data
        return -1;
    }
    if(elem_size <= 0 || elem_count <= 0) { //checking for negative inputs
        return -1;
    }

    for(int i = 0; i < elem_count; i++) { //this loop will run through the data array and use memcmp to check if the target equals a value inside data
        if(memcmp(data, target, elem_size) == 0) {
            return i; //returning the index where the data matches
        }
        else {
            data += elem_size; //bumping the pointer to advance the array
        }
    }
    return -1; //we didn't find a match so return -1
}

bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count) {

    return false;
}

bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count) {

    return false;
}

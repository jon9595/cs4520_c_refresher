#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "../include/arrays.h"

// LOOK INTO MEMCPY, MEMCMP, FREAD, and FWRITE

/* The array_copy function takes in a src array and a dst array. 
 * Also two parameters, elem_size (the size in bytes of each element) and
 * elem_count (total number of elements in the array), are provided.
 * If the memory can be copied into the other array, the fuction returns
 * true, if there are errors with input or the actual copy, the fucntion
 * returns false.
 */
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

/* The array_is_equal function takes in two data elements to compare them 
 * for equality. It uses the memcmp function to do this. The other elements
 * passed in are elem_size and elem_count which help to determine the size of
 * the elements. IF the comparison is good, the memcmp function will return 0,
 * which means we should return true. If it fails, or an error check fails,
 * we should return false.
 */
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

/* The array_location function takes in a data array and a target element.
 * The purpose is to test and see if the target is contained within the data array.
 * Like the above functions, elem_size and elem_count are provided to assist in
 * determining the size of each element and array. The function uses memcmp to 
 * determine if the target is in the data. If it is, it returns i, which
 * corresponds to the index of the element in the data array. During the loop,
 * if there isn't a match, but there is more data in the array, the data array is
 * incremented by the size of a single element to move forward in the array.
 * If the element is found, i is returned, but if the error checks fail
 * or the element is not inside of the data array, -1 is returned.
 */
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

/* The array_serialize function takes in a src_data and dst_file which is a file name.
 * First checks are done to ensure the file name and the data are not null, then a
 * check to ensure the file name is not an empty string or a new line char. It then opens
 * the file for writing in binary and uses the fwrite function to put the data into the file.
 * If fwrite returns 0, that means the function failed to write out the file. If this all works,
 * the file is closed and true is returned. If it wasn't a good write, the file is still closed
 * and false is returned.
 */
bool array_serialize(const void *src_data, const char *dst_file, const size_t elem_size, const size_t elem_count) {

    if(src_data == NULL || dst_file == NULL) { //checking for null inputs
        return false;
    } 

    if(elem_size <= 0 || elem_count <= 0) { //checking for negative inputs
        return false;
    }

    if(strcmp(dst_file, "") == 0 || strcmp(dst_file, "\n") == 0) { //checking for bad file names
        return false;
    }

    FILE* fp = fopen(dst_file, "wb"); //opening a file using the passed in filename for writing in binary

    if(fwrite(src_data, elem_size, elem_count, fp) != 0) { //checking to see if the write actually worked
        fclose(fp);
        return true;
    }
    else { //if 0 items were written to the file, return false
        fclose(fp);
        return false;
    }
}

/* The array_deserialize function takes in a src_file name and dst_data. It then reads in a binary file
 * into the dst_data array. If this works we close the file and return true, if not we still close the 
 * file but return false. 
 */
bool array_deserialize(const char *src_file, void *dst_data, const size_t elem_size, const size_t elem_count) {

    if(src_file == NULL || dst_data == NULL) { //checking for null file names
        return false;
    }

    if(elem_size <= 0 || elem_count <= 0) { //checking to make sure the inputs are non-negative
        return false;
    }

    if(strcmp(src_file, "") == 0 || strcmp(src_file, "\n") == 0) { //checking for bad file names
        return false;
    }

    FILE* fp = fopen(src_file, "rb"); //opening the source file for reading in binary

    int result = fread(dst_data, elem_size, elem_count, fp); //this will read the contents of the binary file into an array. This also will result in the number of elements read in being returned

    if(result != elem_count) { //checking to make sure the correct number of elements was read in
        fclose(fp);
        return false;
    }
    else { //the correct number of elements were read in, so we can return true
        fclose(fp);
        return true;
    }
}

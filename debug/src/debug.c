#include "../include/debug.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

// protected function, that only this .c can use
int comparator_func(const void *a, const void *b) {
    return *(uint8_t *)a - *(uint8_t *)b; //had to dereference the pointers to get the correct result
}

bool terrible_sort(uint16_t *data_array, const size_t value_count) {
    if(data_array == NULL) { //checking for NULL input data
        return false;
    }

    if(value_count == 0) { //checking for a bad value_count
        return false;
    }

    uint16_t* sorting_array = malloc(value_count * sizeof(uint16_t)); //changed from original. Mallocing the correct number of bytes here

    for (unsigned int i = 0; i < value_count; ++i) { //adding the values to the newly alloced array
        sorting_array[i] = data_array[i];
    }

    qsort(sorting_array, value_count, sizeof(uint16_t), comparator_func); //passed the sorting_array, and the number of elements to qsort alonge with the size of each element and the comparator function above

    bool sorted = true; 
    for (unsigned int i = 1; i < value_count; ++i) {
        sorted &= sorting_array[i - 1] <= sorting_array[i]; //checking to ensure the elements are in order
    }

    if (sorted) { //if the sorted var is still true (which means the array is in order) copy the bytes into the source array
        memcpy(data_array, sorting_array, value_count * sizeof(uint16_t));
    } 
    free(sorting_array); //clean up the malloced array
    return sorted;
}


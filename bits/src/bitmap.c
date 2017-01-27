#include "../include/bitmap.h"
#include <math.h>

// data is an array of uint8_t and needs to be allocated in bitmap_create
//      and used in the remaining bitmap functions. You will use data for any bit operations and bit logic
// bit_count the number of requested bits, set in bitmap_create from n_bits
// byte_count the total number of bytes the data contains, set in bitmap_create


bitmap_t *bitmap_create(size_t n_bits) {

    if(n_bits <= 0) {
        return NULL;
    }

    size_t n_bytes = ceil(n_bits/8.0); // calculating total bytes (8 bits = 1 byte)
    bitmap_t* map = malloc(sizeof(bitmap_t)); //creating a bitmap
    map->bit_count = n_bits; //setting its bits
    map->byte_count = n_bytes; //setting bytes that we calculated above
    map->data = calloc(map->byte_count, sizeof(*map->data)); //initializing the data array to all 0s

    return map;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit) {

    if(bitmap == NULL || bitmap->bit_count <= bit) { //checking for bad input
        return false;
    }

    if(bit < 0) { //checking to make sure bit is in range
        return false;
    }

    bitmap->data[bit/8] |= (uint8_t)1 << (bit & 7); //shifting in 0's then ORing it with the byte to add the zeros in

    return true;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit) {

    if(bitmap == NULL || bitmap->bit_count <= bit) { //checking for bad input
        return false;
    }

    if(bit < 0) { //making sure the bit was in range
        return false;
    }

    bitmap->data[bit/8] &= ~((uint8_t)1 << (bit & (7))); //shifting in 0's to replace the 1's we need to get rid of

    return true;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit) {

    if(bitmap == NULL) { //checking for a null bitmap
        return false;
    }

    if(bitmap->bit_count <= bit) { //making sure the bit is actually in range
        return false;
    }

    if((bitmap->data[bit/8] >> (bit & 7)) == 1) { //shifting the passed byte by the number of bits to check if the requested bit is 1
        return true; 
    }
    else { //the requested bit was 0
        return false;
    }
}

size_t bitmap_ffs(const bitmap_t *const bitmap) {

    if(bitmap == NULL) { //checking for a null bitmap
        return SIZE_MAX;
    }

    int i;
    bool set_return;
    for(i = 0; i < bitmap->bit_count; i++) {
        set_return = bitmap_test(bitmap, i); //this will return true when the first 1 is found

        if(set_return == true) { //if a 1 is found return true
            return i;
        }
    }
    return SIZE_MAX; //we didn't find a set bit so return SIZE_MAX
}

size_t bitmap_ffz(const bitmap_t *const bitmap) {

    if(bitmap == NULL) { //checking for a null bitmap
        return SIZE_MAX;
    }

    int i;
    for(i = 0; i < bitmap->byte_count; i++) { //loops through each individual byte
        if(bitmap->data[i] != 255) { //checking to see if the byte is 255 (1111 1111 in binary)
            if(bitmap_test(bitmap, i * 8)) { //if its not 255, check and see if the bits nicely work out
                continue;    
            }
            else {
                int inverted = ~bitmap->data[i]; //this inverts the input byte
                int twos = ~inverted + 1; //this takes the twos complement of the inverted number
                int and = inverted & twos; //bitwise ANDS the inverted input and its 2's comp
                return (i * 8) + log(and)/log(2); //takes the log base 2 of the AND result. log(x)/log(2) is the same as taking log base 2 of (x) then it adds this result (which gives the position of the first zero in the byte) to i * 8 which is the last bits that were not a zero
            }
        }
    }
    return SIZE_MAX; // if no zeros are found, return SIZE_MAX
}

bool bitmap_destroy(bitmap_t *bitmap) {

    if(bitmap == NULL) { //checking to see if the bitmap is already NULL
        return false;
    }

    free(bitmap->data); //freeing the data array
    free(bitmap); //frees the entire struct

    return true; //we cleared the bitmap correctly
}

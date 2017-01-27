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

    bitmap_t* map = malloc(n_bits);
    map->bit_count = n_bits;
    map->byte_count = ceil(n_bits/8.0);
    map->data = calloc(map->byte_count, sizeof(*map->data));

    return map;
}

bool bitmap_set(bitmap_t *const bitmap, const size_t bit) {

    if(bitmap == NULL || bitmap->bit_count <= bit) {
        return false;
    }

    if(bit < 0) {
        return false;
    }

    bitmap->data[bit/8] |= (uint8_t)1 << (bit & 7);

    return true;
}

bool bitmap_reset(bitmap_t *const bitmap, const size_t bit) {

    if(bitmap == NULL || bitmap->bit_count <= bit) {
        return false;
    }

    if(bit < 0) {
        return false;
    }

    bitmap->data[bit/8] &= ~((uint8_t)1 << (bit & (7)));

    return true;
}

bool bitmap_test(const bitmap_t *const bitmap, const size_t bit) {

    if(bitmap == NULL) {
        return false;
    }

    if(bitmap->bit_count <= bit) {
        return false;
    }

    if((bitmap->data[bit/8] >> (bit & 7)) == 1) {
        return true;
    }
    else {
        return false;
    }
}

size_t bitmap_ffs(const bitmap_t *const bitmap) {

    return 0;
}

size_t bitmap_ffz(const bitmap_t *const bitmap) {

    return 0;
}

bool bitmap_destroy(bitmap_t *bitmap) {

    if(bitmap == NULL) {
        return false;
    }

    free(bitmap->data);
    free(bitmap);

    return true;
}

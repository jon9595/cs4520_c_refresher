
#include "../include/structures.h"
#include <stdio.h>

int compare_structs(sample_t* a, sample_t* b)
{
    if(a == NULL || b == NULL) { //checking for bad inputs
        return 0;
    }

    if(a->a != b->a) { //ensuring that a's member a = b's member a
        return 0;
    }

    if(a->b != b->b) {
        return 0;
    }

    if(a->c != b->c) {
        return 0;
    }

    return 1; //the structs matched
}

void print_alignments()
{
    printf("Alignment of int is %zu bytes\n",__alignof__(int));
    printf("Alignment of double is %zu bytes\n",__alignof__(double));
    printf("Alignment of float is %zu bytes\n",__alignof__(float));
    printf("Alignment of char is %zu bytes\n",__alignof__(char));
    printf("Alignment of long long is %zu bytes\n",__alignof__(long long));
    printf("Alignment of short is %zu bytes\n",__alignof__(short));
    printf("Alignment of structs are %zu bytes\n",__alignof__(fruit_t));
}

int sort_fruit(const fruit_t* a,int* apples,int* oranges, const size_t size)
{
    if(a == NULL || apples == NULL || oranges == NULL) { //checking for NULL inputs
        return -1;
    }
    if(size <= 0) { //checking for a bad size input
        return -1;
    }

    for(unsigned int i = 0; i < size; i++) {
        if(a[i].type == 1) { //finding a 1 means this is an apple
            *(apples) += 1;
        }
        else { //this means the element is an orange
            *(oranges) += 1;
        }
    }

    return size; //size was already passed, and it is the size of the array so pass this back
}

int initialize_array(fruit_t* a, int apples, int oranges)
{
    if(a == NULL) { //checking for bad input array
        return -1;
    }

    if(apples < 0 || oranges < 0) { //checking for negative inputs
        return -1;
    }

    int i = 0, j = 0;

    for(i = 0; i < apples; i++) {
        initialize_apple((apple_t*)a + i); //casting a as an apple then using pointer arithmitic to increment the pointer to the next item
    }

    for(j = i; j < i + oranges; j++) { //starting this loop where the last loop left off
        initialize_orange((orange_t*)a + i); //doing the same pointer casting as we did above
    }

    return 0;
}

int initialize_orange(orange_t* a)
{
    if(a == NULL) { //checking for NULL inputs
        return -1;
    }

    //setting all orange attributes to 0 (type = 0 indicated oranges)
    a->peeled = 0;
    a->type = 0;
    a->weight = 0;

    return 0; //initialization worked
}

int initialize_apple(apple_t* a)
{
    if(a == NULL) { //checking for NULL inputs
        return -1;
    }

    //setting all attributes to 0, and type to 1, which represents an apple
    a->type = 1;
    a->weight = 0;
    a->worms = 0;

    return 0;
}

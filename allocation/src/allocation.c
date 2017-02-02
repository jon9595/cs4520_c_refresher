#include "../include/allocation.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>

void* allocate_array(size_t member_size, size_t nmember, bool clear)
{
    if(member_size <= 0 || nmember <= 0) { //checking for negative inputs
        return NULL;
    }

    void* array = NULL; //initializing the array

    if(clear == true) { //if the flag is set, we need to use calloc
        array = (void*) calloc(nmember, member_size);
    }
    else { //if the flag is not set, we use malloc to create the array
        array = (void*) malloc(nmember * member_size);
    }

    return array; //returning the newly alloced array
}

void* reallocate_array(void* ptr, size_t size)
{
    void* ptr_return = NULL; //declaring the return pointer to the array

    ptr_return = realloc(ptr, size); //reallocating the array

    return ptr_return; //returning the realocated array
}

void deallocate_array(void** ptr)
{
    if(ptr == NULL) { //checking if the array is already NULL
        return;
    }

    free(*ptr); //freeing the data

    *ptr = NULL; //setting the pointer to NULL after it is freed

    ptr = NULL; //setting the actual pointer into the array to null

    return; //returning nothing because the functin is of return type void
}

char* read_line_to_buffer(char* filename)
{
    if(filename == NULL) { //checking for a bad input filename
        return NULL;
    }

    FILE* fp = fopen(filename, "r"); //opening the file for reading

    if(fp == NULL) { //checking that the file opened correctly
        return NULL;
    }

    fseek(fp, 0, SEEK_END); //jumping to the end of the file
    long file_size = ftell(fp); //determining the size of the file
    rewind(fp); //setting the file pointer to the begining

    char* buffer = (char*) malloc(sizeof(char) * file_size); //creating a buffer to read in the info into
    memset(buffer, '\0', sizeof(buffer)); //setting all data in the buffer to the NULL terminator

    int c;
    int i = 0;

    do {
        c = fgetc(fp); //getting each char from the input until the end of file is found
        if(c != EOF) {
            buffer[i] = c;
        }
        i++;
    } while(c != EOF);

    fclose(fp); //closing the file

    return buffer; //returning the newly read buffer
}

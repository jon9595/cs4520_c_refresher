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
    if(member_size <= 0 || nmember <= 0) {
        return NULL;
    }

    void* array = NULL; //initializing the array

    if(clear == true) { //if the flag is set, we need to use calloc
        array = (void*) calloc(nmember, member_size);
    }
    else { //if the flag is not set, we use malloc to create the array
        array = (void*) malloc(nmember * member_size);
    }

    return array;
}

void* reallocate_array(void* ptr, size_t size)
{
    void* ptr_return = NULL;

    ptr_return = realloc(ptr, size);

    return ptr_return;
}

void deallocate_array(void** ptr)
{
    if(ptr == NULL) {
        return;
    }

    free(*ptr);

    *ptr = NULL;

    ptr = NULL;

    return;
}

char* read_line_to_buffer(char* filename)
{
    if(filename == NULL) {
        return NULL;
    }

    FILE* fp = fopen(filename, "r");

    if(fp == NULL) {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    long file_size = ftell(fp);
    rewind(fp);

    char* buffer = (char*) malloc(sizeof(char) * file_size);
    memset(buffer, '\0', sizeof(buffer));

    int c;
    int i = 0;

    do {
        c = fgetc(fp);
        if(c != EOF) {
            buffer[i] = c;
        }
        i++;
    } while(c != EOF);

    fclose(fp);

    return buffer;
}

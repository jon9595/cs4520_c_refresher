#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/error_handling.h"

int create_blank_records(Record_t **records, const size_t num_records) {

    if(*records != NULL || num_records == 0 || records == NULL) { //checking for a non-null *records pointer, a 0 number of records and a NULL records pointer
        return -1;
    }

    if(num_records > SIZE_MAX) { //checking for a bad number of num_records. size_t is unsigned so setting it to < 0 will result in a huge size of num_records
        return -2;
    }

    *records = (Record_t*) malloc(sizeof(Record_t) * num_records);

    if(*records == NULL) { //checking to ensure the pointer was malloced correctly
        return -2;
    }

    memset(*records,0,sizeof(Record_t) * num_records); //setting all values in the records array to 0

    return 0; //mission accomplished
}

int read_records(const char *input_filename, Record_t *records, const size_t num_records) {

    if(input_filename == NULL || records == NULL) { //checking for NULL inputs
        return -1;
    }

    if(num_records == 0) { //checking for a 0 record input
        return -1;
    }

    int fd = open(input_filename, O_RDONLY); //opening the file for reading

    if(fd < 0) { //file failed to open
        return -2;
    }

    ssize_t data_read = 0; //setting the initial size of the bytes read
    for (size_t i = 0; i < num_records; ++i) {
        data_read = read(fd,&records[i], sizeof(Record_t)); //reading in the data into each record in the array

        if(data_read != sizeof(Record_t)) { //if the number of bytes read does not equal the size of a record, there was a read error
            return -3;
        }
    }
    return 0;
}

int create_record(Record_t **new_record, const char* name, int age) {

    if(*new_record != NULL || name == NULL) { //checking to ensure the new_record is NULL and the name parameter is not null
        return -1;
    }

    if(age < 1 || age > 200) { //checking for an out of bound age
        return -1;
    }

    if(strcmp(name, "\n") == 0) { //the bad input name that is passed contains a newline char so we need to check for this
        return -1;
    }

    if(strlen(name) > 50) { //checking that the length of the input string is of the right length
        return -1;
    }

    *new_record = (Record_t*) malloc(sizeof(Record_t)); //creating space for a new record

    if(*new_record == NULL) { //checking for bad memory allocation
        return -2;
    }

    memcpy((*new_record)->name,name,sizeof(char) * strlen(name)); //copying in the new data
    (*new_record)->name[MAX_NAME_LEN - 1] = 0;	//ending the string correctly
    (*new_record)->age = age; //setting the age

    return 0;
}

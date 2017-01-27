#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "../include/sys_prog.h"

// LOOK INTO OPEN, READ, WRITE, CLOSE, FSTAT/STAT, LSEEK
// GOOGLE FOR ENDIANESS HELP

bool bulk_read(const char *input_filename, void *dst, const size_t offset, const size_t dst_size) {

    if(input_filename == NULL || dst == NULL) { //checking for NULL inputs
        return false;
    }

    if(offset < 0 || dst_size <= 0) { //checking for negative values
        return false;
    }

    int file = open(input_filename, O_RDONLY); //opening the input file for reading

    if(file <= 0) { //if the file was unable to be opened a number <= 0 is set as the file descriptor
        return false;
    }

    if(lseek(file, offset, SEEK_CUR) != offset) { //seeking in the file for the offset provided
        close(file); 
        return false;
    }

    if((read(file, dst, dst_size)) <= 0) { //reading the data into the dst array
        close(file);
        return false;
    }
    else{
        close(file); //cleaning up upon success
        return true;
    }
}

bool bulk_write(const void *src, const char *output_filename, const size_t offset, const size_t src_size) {
    if(src == NULL || output_filename == NULL) { // checking for NULL inputs
        return false;
    }

    if(offset < 0 || src_size <= 0) { //checking for negative inputs
        return false;
    }

    int file = open(output_filename, O_WRONLY); //opening the file for writing

    if(file <= 0) { //error check to ensure the file was opened correctly
        return false;
    }

    if(lseek(file, offset, SEEK_CUR) != offset) { //seeking as we did in the read function
        close(file);
        return false;
    }

    if((write(file, src, src_size)) <= 0) { //writing out to the file from the source array and checking the number of bytes it wrote
        close(file);
        return false;
    }
    else {
        close(file); //cleaning up
        return true;
    }
}


bool file_stat(const char *query_filename, struct stat *metadata) {

    if(query_filename == NULL || metadata == NULL) { //checking for NULL inputs
        return false;
    }

    int file = open(query_filename, O_RDONLY); //opening the file for reading

    if(file <= 0) { //checking for a good file open
        return false;
    }

    if(fstat(file, metadata) < 0) { //using fstat to pull the metadata from the input file, a result < 0 indicates that the reading of the data failed
        close(file);
        return false;
    }
    else {
        close(file); //cleaning up
        return true;
    }
}

bool endianess_converter(uint32_t *src_data, uint32_t *dst_data, const size_t src_count) {

    if(src_data == NULL || dst_data == NULL) { //error checks for NULL inputs
        return false;
    }

    if(src_count <= 0) { //ensuring the source has content
        return false;
    }

    int i; 
    uint32_t input, byte1, byte2, byte3, byte4; //declaring the variables we need for the swap
    for(i = 0; i < src_count; i++) {
        input = src_data[i]; //pulling the first data item from the input

        byte1 = ((input>>24)&0x000000ff); //shifting the furthest left bit all the way to the right and then anding it with hex to ensure its a 32 bit int
        byte2 = ((input<<8)&0xff000000); //moving the furthest left byte over 2 places to put it as the 2nd from the left byte
        byte3 = ((input>>8)&0xff000000); //moving the furthest left byte into the 2 place from the right
        byte4 = ((input<<24)&0xff000000);//moving the furthest left byte to the furthest right bit

        dst_data[i] = byte1 | byte2 | byte3 | byte4; //the ORing of these bytes will create the full uint32 that has been swapped
    }

    return true;
}

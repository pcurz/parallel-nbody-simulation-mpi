#include "file_io.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Reads values from a binary file into a data buffer.
 * 
 * @param filename Name of the binary file to read.
 * @param data Pointer to the buffer to store the read values.
 * @param bytes Number of bytes to read from the file.
 */
void read_values_from_file(const char* filename, float* data, int bytes) {
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    size_t read_bytes = fread(data, 1, bytes, fp);
    if (read_bytes != bytes) {
        fprintf(stderr, "Error reading data from file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    fclose(fp);
}

/**
 * @brief Writes values from a data buffer to a text file.
 * 
 * @param filename Name of the text file to write.
 * @param data Pointer to the buffer containing data to write.
 * @param count Total number of elements to write.
 */
void write_valuesText_to_file(const char* filename, float* data, int count) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file %s\n", filename);
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%f ", data[i]);
        if ((i + 1) % 6 == 0)
            fprintf(fp, "\n");
    }
    fclose(fp);
}

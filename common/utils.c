//
// Created by romain on 10/12/24.
//

#include "utils.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#define REALLOC_FAILED_MSG "realloc failed"

// works only for 1D array
int reallocate_int_array(int **array_ptr, const size_t new_count) {
    const size_t new_size = new_count * sizeof(int);

    int *new_array = (int *) realloc(*array_ptr, new_size);
    if (new_array == NULL) {
        if (*array_ptr != NULL) {
            free(*array_ptr);
        }
        die_err(REALLOC_FAILED_MSG);
    }
    *array_ptr = new_array;
    return 1;
}

void reallocate_str_array(char ***array_ptr, const size_t new_count) {
    const size_t new_size = new_count * sizeof(char *);

    char **new_array = (char **) realloc(*array_ptr, new_size);
    if (new_array == NULL) {
        if (*array_ptr != NULL) {
            free(*array_ptr);
        }
        die_err(REALLOC_FAILED_MSG);
    }
    *array_ptr = new_array;
}

void read_file(const char *path, void *data, void (*process_file_ptr)(FILE *, void *)) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        die_err("fopen() failed");
    }

    process_file_ptr(file, data);

    if (fclose(file) != 0) {
        die_err("fclose() failed");
    }
    file = NULL;
}

void die_err(const char *message) {
    if (errno) {
        perror(message);
    } else {
        fprintf(stderr, message);
    }
    exit(EXIT_FAILURE);
}

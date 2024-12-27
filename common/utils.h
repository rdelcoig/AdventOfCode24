//
// Created by romain on 3/12/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define COMPARE(l,r) ((l < r) ? -1 : (l > r))

typedef struct {
    unsigned long long part_1;
    unsigned long long part_2;
} Answer2Parts;

int reallocate_int_array(int **array_ptr, size_t new_count);

void read_file(const char *path, void *data, void (*process_file_ptr)(FILE *, void *));

#endif //UTILS_H

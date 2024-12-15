//
// Created by romain on 15/12/24.
//

#ifndef SET_H
#define SET_H

#include <stddef.h>

int contains_set_value(const int *set, const size_t count, const int key, size_t *index);

int add_set_value(int **ptr, const size_t count, const int value);

#endif //SET_H

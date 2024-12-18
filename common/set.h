//
// Created by romain on 15/12/24.
//

#ifndef SET_H
#define SET_H

#include <stddef.h>

typedef struct {
    int *values;
    size_t count;
    size_t capacity;
} SetInt;

SetInt *create_set_int();

void free_set_int(SetInt *set);

int contains_value_set_int(const SetInt *set, const int key, size_t *index);

int add_value_set_int(SetInt *set, const int value);

void clear_set_int(SetInt *set);

#endif //SET_H

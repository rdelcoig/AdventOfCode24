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

SetInt *create_set();

void free_set(SetInt *set);

int contains_set_value(const SetInt *set, const int key, size_t *index);

int add_set_value(SetInt *set, const int value);

void clear_set(SetInt *set);

#endif //SET_H

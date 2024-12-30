//
// Created by romain on 15/12/24.
//

#ifndef SET_H
#define SET_H

#include <stddef.h>

typedef struct {
    char **values;
    size_t count;
    size_t capacity;
} Set;

Set *create_set();

void free_set(Set *set);

int contains_set_value(const Set *set, const char *key);

int add_set_value(Set *set, char *value);

void clear_set(Set *set);

#endif //SET_H

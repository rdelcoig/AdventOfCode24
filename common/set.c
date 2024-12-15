//
// Created by romain on 15/12/24.
//

#include "set.h"

#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

static int int_compare(const void *left, const void *right) {
    const int int_left = *(int *) left;
    const int int_right = *(int *) right;
    return COMPARE(int_left, int_right);
}

int contains_set_value(const int *set, const size_t count, const int key, size_t *index) {
    if (set == NULL) {
        return 0;
    }

    const int *value = bsearch(&key, set, count, sizeof(int), int_compare);
    if (value != NULL && index != NULL) {
        *index = value - set;
    }
    return value != NULL;
}

int add_set_value(int **ptr, const size_t count, const int value) {
    if (contains_set_value(*ptr, count, value, NULL)) {
        return 0;
    }
    if (!reallocate_int_array(ptr, count + 1)) {
        return 0;
    }
    (*ptr)[count] = value;
    qsort(*ptr, count + 1, sizeof(int), int_compare);
    return 1;
}

//
// Created by romain on 15/12/24.
//

#include "set.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_CAPACITY 4

int compare_string(const void *left, const void *right) {
    char *const *left_str = left;
    char *const *right_str = right;
    return strcmp(*left_str, *right_str);
}

Set *create_set() {
    Set *set = malloc(sizeof(Set));
    set->capacity = BASE_CAPACITY;
    set->values = calloc(BASE_CAPACITY, sizeof(char *));
    set->count = 0;
    return set;
}

void free_set(Set *set) {
    if (set == NULL) {
        return;
    }
    if (set->values != NULL) {
        for (size_t i = 0; i < set->capacity; i++) {
            if (set->values[i] != NULL) {
                free(set->values[i]);
            }
        }

        free(set->values);
        set->values = NULL;
    }
    set->count = 0;
    set->capacity = 0;
    free(set);
    set = NULL;
}

int contains_set_value(const Set *set, const char *key) {
    if (set == NULL || set->values == NULL) {
        return 0;
    }

    char **value = (char **) bsearch(&key, set->values, set->count, sizeof(char *), compare_string);
    return value != NULL;
}

int add_set_value(Set *set, char *value) {
    if (contains_set_value(set, value)) {
        return 0;
    }

    set->count++;

    if (set->capacity <= set->count) {
        set->capacity *= 2;
        reallocate_str_array(&set->values, set->capacity);
    }

    const size_t max_buffer_size = 1024;
    char buffer[max_buffer_size];
    strncpy(buffer, value, max_buffer_size);
    const size_t len = strlen(buffer); // strlen is char count without \0

    *(set->values + set->count - 1) = calloc(len + 1, sizeof(char));
    strncpy(*(set->values + set->count - 1), buffer, len + 1);

    qsort(set->values, set->count, sizeof(char *), compare_string);
    return 1;
}

void clear_set(Set *set) {
    if (set == NULL) {
        return;
    }
    for (size_t i = 0; i < set->count; i++) {
        free(set->values[i]);
        set->values[i] = NULL;
    }
    set->count = 0;
}

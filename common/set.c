//
// Created by romain on 15/12/24.
//

#include "set.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BASE_CAPACITY 4

static int set_compare(const void *a, const void *b) {
    return strcmp((const char *) a, (const char *) b);
}

Set *create_set() {
    Set *set = malloc(sizeof(Set));
    set->capacity = BASE_CAPACITY;
    set->values = malloc(BASE_CAPACITY * sizeof(char *));
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

int contains_set_value(Set *set, char *key) {
    if (set == NULL || set->values == NULL) {
        return 0;
    }

    char **value = (char **) bsearch(&key, set->values, set->count, sizeof(char *), set_compare);
    return value != NULL;
}

int add_set_value(Set *set, char *value) {
    if (contains_set_value(set, value)) {
        return 0;
    }

    if (set->capacity <= set->count) {
        set->capacity *= 2;
        reallocate_str_array(&set->values, set->capacity);
    }

    const size_t max_buffer_size = 1024;
    char buffer[max_buffer_size];
    strncpy(buffer, value, max_buffer_size);
    const size_t len = strlen(buffer);

    set->values[set->count] = malloc(len * sizeof(char));
    strncpy(set->values[set->count], buffer, len);

    set->count++;
    qsort(set->values, set->count, sizeof(char *), set_compare);

    return 1;
}


static int int_compare(const void *left, const void *right) {
    const int int_left = *(int *) left;
    const int int_right = *(int *) right;
    return COMPARE(int_left, int_right);
}

int contains_value_set_int(const SetInt *set, const int key, size_t *index) {
    if (set == NULL || set->values == NULL) {
        return 0;
    }

    const int *value = bsearch(&key, set->values, set->count, sizeof(int), int_compare);
    if (value != NULL && index != NULL) {
        *index = value - set->values;
    }
    return value != NULL;
}

int add_value_set_int(SetInt *set, const int value) {
    if (contains_value_set_int(set, value, NULL)) {
        return 0;
    }

    if (set->capacity <= set->count) {
        set->capacity *= 2;
        if (!reallocate_int_array(&set->values, set->capacity)) {
            return 0;
        }
    }

    set->values[set->count] = value;
    set->count++;
    qsort(set->values, set->count, sizeof(int), int_compare);

    return 1;
}

void clear_set_int(SetInt *set) {
    if (set == NULL) {
        return;
    }
    for (size_t i = 0; i < set->count; i++) {
        set->values[i] = 0;
    }
    set->count = 0;
}

SetInt *create_set_int() {
    SetInt *set = malloc(sizeof(SetInt));
    set->capacity = BASE_CAPACITY;
    set->values = malloc(BASE_CAPACITY * sizeof(int));
    set->count = 0;
    return set;
}

void free_set_int(SetInt *set) {
    if (set == NULL) {
        return;
    }
    if (set->values != NULL) {
        free(set->values);
        set->values = NULL;
    }
    set->count = 0;
    set->capacity = 0;
    free(set);
    set = NULL;
}

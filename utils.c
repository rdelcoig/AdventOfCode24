//
// Created by romain on 10/12/24.
//

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

inline Point add_points(const Point *point1, const Point *point2) {
    return (Point){point1->x + point2->x, point1->y + point2->y};
}

inline int is_out_of_bounds(const TableSize *size, const Point *point) {
    return point->x < 0 || point->x >= size->columns || point->y < 0 || point->y >= size->lines;
}

inline int equals(const Point *left, const Point *right) {
    return left->x == right->x && left->y == right->y;
}

int reallocate_int_array(int **array, const size_t new_count) {
    int *new_array = realloc(*array, new_count * sizeof(int *));
    if (new_array == NULL) {
        perror("Out of memory");
        return 0;
    }
    *array = new_array;
    return 1;
}

// TODO should be removed
int reallocate_int_jagged_array(int ***array, const int new_count) {
    int **new_array = realloc(*array, new_count * sizeof(int *));
    if (new_array == NULL) {
        perror("Out of memory");
        return 0;
    }
    *array = new_array;
    return 1;
}

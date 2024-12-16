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

// works only for 1D array
int reallocate_int_array(int **array_ptr, const size_t new_count) {
    int *array = *array_ptr;
    const size_t new_size = new_count * sizeof(int);

    int *new_array = (int *) realloc(array, new_size);
    if (new_array == NULL) {
        printf("Error: not enough memory\n");
        if (array != NULL) {
            free(array);
        }
        exit(1);
    }
    *array_ptr = new_array;
    return 1;
}

//
// Created by romain on 10/12/24.
//

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

inline Point add_points(const Point *point1, const Point *point2) {
    return (Point){point1->x + point2->x, point1->y + point2->y};
}

void set_point(Point *receiving_point, const Point point_new_val) {
    receiving_point->x = point_new_val.x;
    receiving_point->y = point_new_val.y;
}

int is_out_of_bounds(const TableSize *size, const Point *point) {
    return point->x < 0 || point->x >= size->columns || point->y < 0 || point->y >= size->lines;
}

inline int equals(const Point *left, const Point *right) {
    return (left == NULL && right == NULL)
           || (left != NULL
               && right != NULL
               && (left->x == right->x && left->y == right->y));
}

// works only for 1D array
int reallocate_int_array(int **array_ptr, const size_t new_count) {
    const size_t new_size = new_count * sizeof(int);

    int *new_array = (int *) realloc(*array_ptr, new_size);
    if (new_array == NULL) {
        printf("Error: not enough memory\n");
        if (*array_ptr != NULL) {
            free(*array_ptr);
        }
        exit(1);
    }
    *array_ptr = new_array;
    return 1;
}

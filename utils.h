//
// Created by romain on 3/12/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>

#define COMPARE(l,r) ((l < r) ? -1 : (l > r))

typedef struct {
    int part_1;
    int part_2;
} Answer2Parts;

typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    int lines;
    int columns;
} TableSize;

Point add_points(const Point *point1, const Point *point2);

int reallocate_int_array(int **array, const size_t new_count);

int reallocate_int_jagged_array(int ***array, const int new_count);

#endif //UTILS_H

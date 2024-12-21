//
// Created by romain on 3/12/24.
//

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>

#define COMPARE(l,r) ((l < r) ? -1 : (l > r))

typedef struct {
    unsigned long long part_1;
    unsigned long long part_2;
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

void set_point(Point *receiving_point, const Point point_new_val);

int is_out_of_bounds(const TableSize *size, const Point *point);

int equals(const Point *left, const Point *right);

int reallocate_int_array(int **array_ptr, size_t new_count);

void read_file(const char *path, void *data, void (*process_file_ptr)(FILE *, void *));

#endif //UTILS_H

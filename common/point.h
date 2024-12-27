//
// Created by romain on 25/12/24.
//

#ifndef POINT_H
#define POINT_H

typedef struct {
    size_t x;
    size_t y;
} Point;

void print_point(const Point *point);

Point add_points(const Point *point1, const Point *point2);

void set_point(Point *receiving_point, const Point point_new_val);

int equals(const Point *left, const Point *right);

#endif //POINT_H

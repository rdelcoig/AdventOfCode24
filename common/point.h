//
// Created by romain on 25/12/24.
//

#ifndef POINT_H
#define POINT_H

typedef struct {
    size_t x;
    size_t y;
} Point;

typedef struct {
    long x_gap;
    long y_gap;
} PointGap;

typedef struct {
    Point point1;
    Point point2;
} PointCouple;

char *point_as_string(const Point *point);

void print_point(const Point *point);

void print_gap(const PointGap *gap);

Point add_points(const Point *point1, const Point *point2);

Point sub_points(const Point *point1, const Point *point2);

PointGap get_point_gap(const PointCouple *couple);

void set_point(Point *receiving_point, const Point point_new_val);

int equals(const Point *left, const Point *right);

Point add_gap(const Point *point, const PointGap *gap);

Point sub_gap(const Point *point, const PointGap *gap);

int reallocate_point_array(Point **array_ptr, const size_t new_count);

#endif //POINT_H

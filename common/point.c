//
// Created by romain on 25/12/24.
//

#include <stdio.h>

#include "point.h"

void print_point(const Point *point) {
    printf("(%zu, %zu)", point->x, point->y);
}

inline Point add_points(const Point *point1, const Point *point2) {
    return (Point){point1->x + point2->x, point1->y + point2->y};
}

void set_point(Point *receiving_point, const Point point_new_val) {
    receiving_point->x = point_new_val.x;
    receiving_point->y = point_new_val.y;
}

inline int equals(const Point *left, const Point *right) {
    return (left == NULL && right == NULL)
           || (left != NULL
               && right != NULL
               && (left->x == right->x && left->y == right->y));
}

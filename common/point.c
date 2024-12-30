//
// Created by romain on 25/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "point.h"

void print_point(const Point *point) {
    printf("(%zu, %zu)", point->x, point->y);
}

char *point_as_string(const Point *point) {
    char buffer[100];
    sprintf(buffer, "(%zu,%zu)", point->x, point->y);
    char *result = malloc(strlen(buffer) + 1);
    strcpy(result, buffer);
    return result;
}

void print_gap(const PointGap *gap) {
    printf("(%ld, %ld)", gap->x_gap, gap->y_gap);
}

inline Point add_points(const Point *point1, const Point *point2) {
    return (Point){point1->x + point2->x, point1->y + point2->y};
}

inline Point sub_points(const Point *point1, const Point *point2) {
    return (Point){point1->x - point2->x, point1->y - point2->y};
}

PointGap get_point_gap(const PointCouple *couple) {
    PointGap gap;
    gap.x_gap = (long) (couple->point2.x - couple->point1.x);
    gap.y_gap = (long) (couple->point2.y - couple->point1.y);
    return gap;
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

Point add_gap(const Point *point, const PointGap *gap) {
    Point result;
    result.x = point->x + gap->x_gap;
    result.y = point->y + gap->y_gap;
    return result;
}

Point sub_gap(const Point *point, const PointGap *gap) {
    Point result;
    result.x = point->x - gap->x_gap;
    result.y = point->y - gap->y_gap;
    return result;
}

int reallocate_point_array(Point **array_ptr, const size_t new_count) {
    const size_t new_size = new_count * sizeof(Point);

    Point *new_array = (Point *) realloc(*array_ptr, new_size);
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

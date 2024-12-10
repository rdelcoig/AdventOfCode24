//
// Created by romain on 3/12/24.
//

#ifndef UTILS_H
#define UTILS_H

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

#endif //UTILS_H

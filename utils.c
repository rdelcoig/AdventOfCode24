//
// Created by romain on 10/12/24.
//

#include "utils.h"

inline Point add_points(const Point *point1, const Point *point2) {
    return (Point){point1->x + point2->x, point1->y + point2->y};
}

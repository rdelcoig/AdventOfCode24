//
// Created by romain on 15/12/24.
//

#ifndef DAY06_MAP_H
#define DAY06_MAP_H

#include "../common/utils.h"
#include "../common/set.h"
#include "../common/matrix_map.h"

#define EMPTY_SPACE '.'
#define OBSTRUCTION '#'

void process_file_day06(FILE *file, MatrixMap **data);

void retrieve_point_from_set(const Set *set, const int index, Point *agent);

void add_move_history(Set *move_history, const Point *from, const Point *to);

#endif //DAY06_MAP_H

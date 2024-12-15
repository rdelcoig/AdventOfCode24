//
// Created by romain on 15/12/24.
//

#ifndef DAY06_MAP_H
#define DAY06_MAP_H

#include "../common/utils.h"

char read_map(const int **map, const TableSize *size, const Point *point);

void write_in_map(int **map, const TableSize *size, const Point *point, const char value);

void print_map(const int **map, const TableSize *size);

void read_file_day06(const char *path, int ***map_ptr, TableSize *size);

#endif //DAY06_MAP_H

//
// Created by romain on 15/12/24.
//

#ifndef DAY06_MAP_H
#define DAY06_MAP_H

#include "../common/utils.h"
#include "../common/set.h"

#define EMPTY_SPACE '.'
#define OBSTRUCTION '#'

char read_map(const int **map, const TableSize *size, const Point *point);

void write_in_map(int **map, const TableSize *size, const Point *point, const char value);

void print_map(const int **map, const TableSize *size);

int **create_map(const TableSize *size);

void copy_map(const int **map_from, int **map_to, const TableSize *size);

int **clone_map(const int **map, const TableSize *size);

void free_map(int ***map, const TableSize *size);

void read_file_day06(const char *path, int ***map_ptr, TableSize *size);

int add_point_to_set(SetInt *set, const Point *point);

void retrieve_point_from_set(const SetInt *set, const int index, Point *agent);

void add_move_history(SetInt *move_history, const Point *from, const Point *to);

#endif //DAY06_MAP_H

//
// Created by romain on 25/12/24.
//

#ifndef MATRIX_MAP_H
#define MATRIX_MAP_H

#include "point.h"

typedef struct {
    size_t lines;
    size_t columns;
} TableSize;

typedef struct {
    char **values;
    TableSize size;
} MatrixMap;

MatrixMap *create_matrix_map(const size_t lines, const size_t columns);

void free_matrix_map(MatrixMap **matrix_map);

void print_matrix_map(const MatrixMap *matrix_map);

void set_value_in_matrix_map(const MatrixMap *matrix_map, const Point *point, const char value);

void set_line_in_matrix_map(const MatrixMap *matrix_map, const size_t line_index, const char *line);

char get_value_in_matrix_map(const MatrixMap *matrix_map, const Point *point);

int is_out_of_bounds(const TableSize *size, const Point *point);

int is_out_of_map(const MatrixMap *map, const Point *point);

void copy_matrix_map(const MatrixMap *source_map, MatrixMap *dest_map);

MatrixMap *clone_matrix_map(const MatrixMap *matrix_map);

void set_matrix_map(MatrixMap *map, const char character);

#endif //MATRIX_MAP_H

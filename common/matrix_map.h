//
// Created by romain on 25/12/24.
//

#ifndef MATRIX_MAP_H
#define MATRIX_MAP_H

typedef struct {
    size_t x;
    size_t y;
} Point;

typedef struct {
    size_t lines;
    size_t columns;
} TableSize;

typedef struct {
    char **map;
    TableSize size;
} MatrixMap;

MatrixMap *create_matrix_map(const size_t lines, const size_t columns);

void free_matrix_map(MatrixMap **matrix_map);

void print_matrix_map(const MatrixMap *matrix_map);

void set_value_in_matrix_map(const MatrixMap *matrix_map, const Point *point, const char value);

void set_line_in_matrix_map(const MatrixMap *matrix_map, const size_t line_index, const char *line);

char get_value_in_matrix_map(const MatrixMap *matrix_map, const Point *point);

#endif //MATRIX_MAP_H

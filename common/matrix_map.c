//
// Created by romain on 25/12/24.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "matrix_map.h"

static int is_out_of_bounds(const TableSize *size, const Point *point) {
    return point->x < 0 || point->x >= size->columns || point->y < 0 || point->y >= size->lines;
}

char *get_value_ptr_in_matrix_map(const MatrixMap *matrix_map, const Point *point) {
    if (is_out_of_bounds(&matrix_map->size, point)) {
        printf("Out of bounds\n");
        exit(1);
    }
    return &matrix_map->map[point->y][point->x];
}

MatrixMap *create_matrix_map(const size_t lines, const size_t columns) {
    MatrixMap *matrix_map = malloc(sizeof(MatrixMap));
    matrix_map->size.lines = lines;
    matrix_map->size.columns = columns;
    matrix_map->map = malloc(sizeof(char *) * lines);
    for (size_t i = 0; i < lines; i++) {
        matrix_map->map[i] = calloc(columns, sizeof(char));
    }
    return matrix_map;
}

void free_matrix_map(MatrixMap **matrix_map) {
    if (*matrix_map == NULL) {
        return;
    }
    for (size_t i = 0; i < (*matrix_map)->size.lines; i++) {
        free((*matrix_map)->map[i]);
        (*matrix_map)->map[i] = NULL;
    }
    free((*matrix_map)->map);
    (*matrix_map)->map = NULL;
    free(*matrix_map);
    *matrix_map = NULL;
}

void print_matrix_map(const MatrixMap *matrix_map) {
    const TableSize *size = &matrix_map->size;
    char **map = matrix_map->map;
    for (int y = 0; y < size->lines; y++) {
        for (int x = 0; x < size->columns; x++) {
            putchar(map[y][x]);
        }
        putchar('\n');
    }
    putchar('\n');
}

void set_value_in_matrix_map(const MatrixMap *matrix_map, const Point *point, const char value) {
    char *value_ptr = get_value_ptr_in_matrix_map(matrix_map, point);
    *value_ptr = value;
}

void set_line_in_matrix_map(const MatrixMap *matrix_map, const size_t line_index, const char *line) {
    strncpy(matrix_map->map[line_index], line, matrix_map->size.columns);
}

char get_value_in_matrix_map(const MatrixMap *matrix_map, const Point *point) {
    return *get_value_ptr_in_matrix_map(matrix_map, point);
}

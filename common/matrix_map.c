//
// Created by romain on 25/12/24.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "matrix_map.h"

char *get_value_ptr_in_matrix_map(const MatrixMap *matrix_map, const Point *point) {
    if (is_out_of_map(matrix_map, point)) {
        printf("Out of bounds\n");
        exit(1);
    }
    return &matrix_map->values[point->y][point->x];
}

MatrixMap *create_matrix_map(const size_t lines, const size_t columns) {
    MatrixMap *matrix_map = malloc(sizeof(MatrixMap));
    matrix_map->size.lines = lines;
    matrix_map->size.columns = columns;
    matrix_map->values = malloc(sizeof(char *) * lines);
    for (size_t i = 0; i < lines; i++) {
        matrix_map->values[i] = calloc(columns, sizeof(char));
    }
    return matrix_map;
}

void free_matrix_map(MatrixMap **matrix_map) {
    if (*matrix_map == NULL) {
        return;
    }
    for (size_t i = 0; i < (*matrix_map)->size.lines; i++) {
        free((*matrix_map)->values[i]);
        (*matrix_map)->values[i] = NULL;
    }
    free((*matrix_map)->values);
    (*matrix_map)->values = NULL;
    free(*matrix_map);
    *matrix_map = NULL;
}

void print_matrix_map(const MatrixMap *matrix_map) {
    const TableSize *size = &matrix_map->size;
    char **map = matrix_map->values;
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
    strncpy(matrix_map->values[line_index], line, matrix_map->size.columns);
}

char get_value_in_matrix_map(const MatrixMap *matrix_map, const Point *point) {
    return *get_value_ptr_in_matrix_map(matrix_map, point);
}

int is_out_of_map(const MatrixMap *map, const Point *point) {
    return is_out_of_bounds(&map->size, point);
}

int is_out_of_bounds(const TableSize *size, const Point *point) {
    return point->x < 0 || point->x >= size->columns || point->y < 0 || point->y >= size->lines;
}

void copy_matrix_map(const MatrixMap *source_map, MatrixMap *dest_map) {
    if (source_map == NULL || dest_map == NULL) {
        printf("Invalid matrix map\n");
        exit(1);
    }
    for (int y = 0; y < source_map->size.lines; y++) {
        set_line_in_matrix_map(dest_map, y, source_map->values[y]);
    }
}

MatrixMap *clone_matrix_map(const MatrixMap *matrix_map) {
    MatrixMap *copy = create_matrix_map(matrix_map->size.lines, matrix_map->size.columns);
    copy_matrix_map(matrix_map, copy);
    return copy;
}

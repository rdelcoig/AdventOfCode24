//
// Created by romain on 15/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day06_map.h"

char read_map(const int **map, const TableSize *size, const Point *point) {
    if (is_out_of_bounds(size, point)) {
        printf("Read out of bounds: %d %d\n", point->x, point->y);
        exit(1);
    }
    return (char) map[point->y][point->x];
}

void write_in_map(int **map, const TableSize *size, const Point *point, const char value) {
    if (is_out_of_bounds(size, point)) {
        printf("Write out of bounds: %d %d\n", point->x, point->y);
        exit(1);
    }
    map[point->y][point->x] = (int) value;
}

void print_map(const int **map, const TableSize *size) {
    for (int y = 0; y < size->lines; y++) {
        for (int x = 0; x < size->columns; x++) {
            putchar(map[y][x]);
        }
        putchar('\n');
    }
    putchar('\n');
}

int **create_map(const TableSize *size) {
    int **map = malloc(size->lines * sizeof(int *));
    for (int i = 0; i < size->lines; i++) {
        map[i] = malloc(size->columns * sizeof(int));
    }
    return map;
}

void copy_map(const int **map_from, int **map_to, const TableSize *size) {
    if (map_from == NULL || map_to == NULL) {
        printf("Invalid map\n");
        exit(1);
    }

    for (int y = 0; y < size->lines; y++) {
        for (int x = 0; x < size->columns; x++) {
            map_to[y][x] = map_from[y][x];
        }
    }
}

int **clone_map(const int **map, const TableSize *size) {
    int **copy = malloc(size->lines * sizeof(int *));
    for (int y = 0; y < size->lines; y++) {
        copy[y] = malloc(size->columns * sizeof(int));
    }
    copy_map(map, copy, size);
    return copy;
}

void free_map(int ***map, const TableSize *size) {
    if (map == NULL) {
        return;
    }
    if (*map != NULL) {
        for (int i = 0; i < size->lines; i++) {
            if ((*map)[i] != NULL) {
                free((*map)[i]);
                (*map)[i] = NULL;
            }
        }
        free(*map);
        *map = NULL;
    }
    map = NULL;
}

void read_file_day06(const char *path, int ***map_ptr, TableSize *size) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        perror("File not found");
        exit(1);
    }

    size->lines = 0;
    size->columns = 0;

    // read a 1st time to get size
    const int size_buffer = 1024;
    char buffer[size_buffer];
    while (fgets(buffer, size_buffer, file)) {
        size->lines++;
        size->columns = (int) strlen(buffer);
    }

    // init 2D array
    int **map = create_map(size);

    // read again to fill the array
    fseek(file, 0, SEEK_SET);
    int lines_index = 0;
    while (fgets(buffer, size_buffer, file)) {
        for (int columns_index = 0; columns_index < size->columns; columns_index++) {
            map[lines_index][columns_index] = (int) buffer[columns_index];
        }
        lines_index++;
    }

    //print_map(map, size);

    *map_ptr = map;
    fclose(file);
}

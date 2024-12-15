//
// Created by romain on 15/12/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "day06_map.h"

char read_map(const int **map, const TableSize *size, const Point *point) {
    if (is_out_of_bounds(size, point)) {
        printf("Out of bounds: %d %d\n", point->x, point->y);
        exit(1);
    }
    return (char) map[point->y][point->x];
}

void write_in_map(int **map, const TableSize *size, const Point *point, const char value) {
    if (is_out_of_bounds(size, point)) {
        printf("Out of bounds: %d %d\n", point->x, point->y);
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

void read_file_day06(const char *path, int ***map, TableSize *size) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        perror("File not found");
        exit(1);
    }

    int width = 0;
    char c;
    while ((c = fgetc(file)) != EOF) {
        if (c == '\n' && width == 0) {
            break;
        }

        if (size->lines == 0) {
            size->lines++;
            *map = malloc(sizeof(int *));
        }

        int *line = *(*map + size->lines - 1);

        if (c == '\n') {
            reallocate_int_jagged_array(map, size->lines + 1);
            size->lines++;
            size->columns = width;
            width = 0;
        } else {
            reallocate_int_array(&line, width + 1);
            line[width] = (int) c;
            width++;
            (*map)[size->lines - 1] = line;
        }
    }

    fclose(file);
}

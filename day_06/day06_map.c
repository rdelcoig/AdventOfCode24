//
// Created by romain on 15/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day06_map.h"
#include "day06_agent.h"

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
    rewind(file);

    int lines_index = 0;
    while (fgets(buffer, size_buffer, file)) {
        for (int columns_index = 0; columns_index < size->columns; columns_index++) {
            map[lines_index][columns_index] = (int) buffer[columns_index];
        }
        lines_index++;
    }

    *map_ptr = map;
    fclose(file);
}

static int encode_point(const Point *point) {
    return point->x * 10000 + point->y;
}

static void decode_point(const int code, Point *point) {
    const int x = code / 10000;
    const int y = code % 10000;
    point->x = x;
    point->y = y;
}

int add_point_to_set(SetInt *set, const Point *point) {
    const int code = encode_point(point);
    return add_value_set_int(set, code);
}

void retrieve_point_from_set(const SetInt *set, const int index, Point *agent) {
    const int code = set->values[index];
    decode_point(code, agent);
}

void add_move_history(SetInt *move_history, const Point *from, const Point *to) {
    if (move_history == NULL) {
        return;
    }
    if (from == NULL) {
        return;
    }
    if (to == NULL) {
        return;
    }

    Point from_position = *from;
    if (from_position.x == to->x) {
        if (from_position.y <= to->y) {
            for (int y = from_position.y; y <= to->y; y++) {
                from_position.y = y;
                add_point_to_set(move_history, &from_position);
            }
        } else {
            for (int y = from_position.y; y >= to->y; y--) {
                from_position.y = y;
                add_point_to_set(move_history, &from_position);
            }
        }
    } else if (from_position.y == to->y) {
        if (from_position.x <= to->x) {
            for (int x = from_position.x; x <= to->x; x++) {
                from_position.x = x;
                add_point_to_set(move_history, &from_position);
            }
        } else {
            for (int x = from_position.x; x >= to->x; x--) {
                from_position.x = x;
                add_point_to_set(move_history, &from_position);
            }
        }
    }
}

//
// Created by romain on 15/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "day06_map.h"

void process_file_day06(FILE *file, MatrixMap **data) {
    size_t lines = 0;
    size_t columns = 0;

    // read a 1st time to get size
    const int size_buffer = 1024;
    char buffer[size_buffer];
    while (fgets(buffer, size_buffer, file)) {
        lines++;
        columns = (int) strlen(buffer);
    }

    *data = create_matrix_map(lines, columns);

    // read again to fill the array
    rewind(file);

    int lines_index = 0;
    while (fgets(buffer, size_buffer, file)) {
        for (int columns_index = 0; columns_index < (*data)->size.columns; columns_index++) {
            (*data)->values[lines_index][columns_index] = buffer[columns_index];
        }
        lines_index++;
    }
}

int add_point_to_set(SetInt *set, const Point *point) {
    if (point->x > INT_MAX / 1000 || point->y > INT_MAX / 1000) {
        printf("Invalid x %lu y %lu\n", point->x, point->y);
        exit(1);
    }

    const int code = point->x * 1000 + point->y;
    return add_value_set_int(set, code);
}

void retrieve_point_from_set(const SetInt *set, const int index, Point *agent) {
    const int code = set->values[index];
    const int x = code / 1000;
    const int y = code % 1000;
    agent->x = x;
    agent->y = y;
}

void add_move_history(SetInt *move_history, const Point *from, const Point *to) {
    if (move_history == NULL || from == NULL || to == NULL) {
        return;
    }

    Point from_position = *from;
    size_t start, end;
    if (from_position.x == to->x) {
        if (from_position.y <= to->y) {
            start = from_position.y;
            end = to->y;
        } else {
            start = to->y;
            end = from_position.y;
        }
        for (size_t y = start; y <= end; y++) {
            from_position.y = y;
            add_point_to_set(move_history, &from_position);
        }
    } else if (from_position.y == to->y) {
        if (from_position.x <= to->x) {
            start = from_position.x;
            end = to->x;
        } else {
            start = to->x;
            end = from_position.x;
        }
        for (size_t x = start; x <= end; x++) {
            from_position.x = x;
            add_point_to_set(move_history, &from_position);
        }
    }
}

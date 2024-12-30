//
// Created by romain on 15/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "day06_map.h"

#define POINT_FMT "%lu,%lu"

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

static int add_point_to_set(Set *set, const Point *point) {
    size_t size = snprintf(NULL, 0, POINT_FMT, point->x, point->y);
    char buffer[size + 1]; // +1 for terminating null byte
    snprintf(buffer, sizeof buffer, POINT_FMT, point->x, point->y);
    return add_set_value(set, buffer);
}

void retrieve_point_from_set(const Set *set, const int index, Point *agent) {
    const int scanned_args = sscanf(set->values[index], POINT_FMT, &agent->x, &agent->y);
    if (scanned_args != 2) {
        printf("Invalid point %s\n", set->values[index]);
        exit(1);
    }
}

void add_move_history(Set *move_history, const Point *from, const Point *to) {
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

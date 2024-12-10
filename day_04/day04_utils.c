//
// Created by romain on 10/12/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day04_utils.h"

void read_file_day04(const char *path, const TableSize *size, char **raw_data) {
    FILE *file = fopen(path, "r");

    int i = 0;
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1 && i < size->lines) {
        strncpy(raw_data[i], line, size->columns);
        i++;
    }

    fclose(file);
}

int read_file_day04_and_return_answer(const char *file_path, const TableSize *size,
                                      int (*get_total)(char **lines, const TableSize *size)) {
    char *lines[size->lines];
    for (int i = 0; i < size->lines; i++) {
        lines[i] = calloc(size->columns + 1, sizeof(char));
    }

    read_file_day04(file_path, size, lines);
    const int total = get_total(lines, size);

    for (int i = 0; i < size->lines; i++)
        free(lines[i]);

    return total;
}

inline int is_out_of_bounds(const Point *point, const TableSize *size) {
    return point->x < 0 || point->x >= size->columns || point->y < 0 || point->y >= size->lines;
}

char get_value_at_point(char **lines, const TableSize *size, const Point *point) {
    if (is_out_of_bounds(point, size)) {
        perror("Out of bounds");
        exit(1);
    }
    return lines[point->y][point->x];
}

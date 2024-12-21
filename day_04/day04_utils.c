//
// Created by romain on 10/12/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day04_utils.h"

typedef struct {
    const TableSize *size;
    char **raw_data;
} Day04Data;

static void process_file_day04(FILE *file, Day04Data *data) {
    int i = 0;
    const int size_buffer = 200;
    char line[size_buffer];
    while (fgets(line, size_buffer, file) != NULL && i < data->size->lines) {
        strncpy(data->raw_data[i], line, data->size->columns);
        i++;
    }
}

int read_file_day04_and_return_answer(const char *file_path, const TableSize *size,
                                      int (*get_total)(char **lines, const TableSize *size)) {
    char *lines[size->lines];
    for (int i = 0; i < size->lines; i++) {
        lines[i] = calloc(size->columns + 1, sizeof(char));
    }

    Day04Data data = {
        size,
        lines
    };
    read_file(file_path, &data, process_file_day04);

    const int total = get_total(lines, size);

    for (int i = 0; i < size->lines; i++)
        free(lines[i]);

    return total;
}

char get_value_at_point(char **lines, const TableSize *size, const Point *point) {
    if (is_out_of_bounds(size, point)) {
        perror("Out of bounds");
        exit(1);
    }
    return lines[point->y][point->x];
}

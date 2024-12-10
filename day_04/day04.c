//
// Created by romain on 10/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "day04.h"

static void read_file_day04(char **raw_data, const TableSize *size, const int test) {
    const char *path = test ? "../day_04/day04_test.txt" : "../day_04/day04.txt";
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

static int is_out_of_bounds(const Point *point, const TableSize *size) {
    return point->x < 0 || point->x >= size->columns || point->y < 0 || point->y >= size->lines;
}

static int has_next_matching(char **line, const TableSize *size, const Point *current, const Point *direction) {
    Point next = *current;
    const char *next_chars = "MAS";
    for (int i = 0; i < strlen(next_chars); i++) {
        const Point next_tmp = add_points(&next, direction);
        next = next_tmp;

        if (is_out_of_bounds(&next, size)) {
            return 0;
        }
        if (line[next.y][next.x] != next_chars[i]) {
            return 0;
        }
    }
    return 1;
}

static int get_total_around(char **line, const TableSize *size, const Point *current) {
    const Point directions[] = {
        {1, 0},
        {1, -1},
        {0, -1},
        {-1, -1},
        {-1, 0},
        {-1, 1},
        {0, 1},
        {1, 1}
    };

    const unsigned long directions_size = sizeof(directions) / sizeof(directions[0]);

    int total = 0;
    for (int i = 0; i < directions_size; i++) {
        const Point direction = directions[i];
        total += has_next_matching(line, size, current, &direction);
    }
    return total;
}

static int get_total(char **lines, const TableSize *size) {
    int total = 0;
    for (int y = 0; y < size->lines; y++) {
        for (int x = 0; x < size->columns; x++) {
            const char current = lines[y][x];
            if (current == 'X') {
                Point current_position = {x, y};
                total += get_total_around(lines, size, &current_position);
            }
        }
    }
    return total;
}

int get_answer_test() {
    const TableSize size = {10, 10};
    char *lines[size.lines];
    for (int i = 0; i < size.lines; i++) {
        lines[i] = calloc(size.columns + 1, sizeof(char));
    }

    read_file_day04(lines, &size, 1);
    const int total = get_total(lines, &size);

    for (int i = 0; i < size.lines; i++)
        free(lines[i]);

    return total;
}

int get_answer() {
    const TableSize size = {140, 140};
    char *lines[size.lines];
    for (int i = 0; i < size.lines; i++) {
        lines[i] = calloc(size.columns + 1, sizeof(char));
    }

    read_file_day04(lines, &size, 0);
    const int total = get_total(lines, &size);

    for (int i = 0; i < size.lines; i++)
        free(lines[i]);

    return total;
}

void set_day04_answer(Answer2Parts *answer) {
    answer->part_1 = get_answer();
    answer->part_2 = 0;
}

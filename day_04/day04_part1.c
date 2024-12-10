//
// Created by romain on 10/12/24.
//

#include <string.h>

#include "day04_part1.h"
#include "day04_utils.h"
#include "../utils.h"

static int has_next_matching(char **table, const TableSize *size, const Point *current, const Point *direction) {
    Point next = *current;
    const char *next_chars = "MAS";
    for (int i = 0; i < strlen(next_chars); i++) {
        const Point next_tmp = add_points(&next, direction);
        next = next_tmp;

        if (is_out_of_bounds(&next, size)) {
            return 0;
        }

        const char value = get_value_at_point(table, size, &next);
        if (value != next_chars[i]) {
            return 0;
        }
    }
    return 1;
}

static int get_total_around(char **table, const TableSize *size, const Point *current) {
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
        total += has_next_matching(table, size, current, &direction);
    }
    return total;
}

static int get_total(char **table, const TableSize *size) {
    int total = 0;
    for (int y = 0; y < size->lines; y++) {
        for (int x = 0; x < size->columns; x++) {
            Point current_position = {x, y};
            const char current = get_value_at_point(table, size, &current_position);
            if (current == 'X') {
                total += get_total_around(table, size, &current_position);
            }
        }
    }
    return total;
}

int get_answer_part1_test() {
    const TableSize size = {10, 10};
    return read_file_day04_and_return_answer("../day_04/day04_test.txt", &size, get_total);
}

int get_answer_part1() {
    const TableSize size = {140, 140};
    return read_file_day04_and_return_answer("../day_04/day04.txt", &size, get_total);
}

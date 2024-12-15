//
// Created by romain on 10/12/24.
//

#include <string.h>

#include "day04_part2.h"
#include "day04_utils.h"
#include "../utils.h"

static Point get_opposite_corner(const Point *point) {
    const Point opposite = {point->x * -1, point->y * -1};
    return opposite;
}

static int has_word(char **table, const TableSize *size, const Point *current, const Point *corner) {
    Point point = add_points(current, corner);
    if (is_out_of_bounds(size, &point)) {
        return 0;
    }

    const char value1 = get_value_at_point(table, size, &point);
    if (value1 != 'M' && value1 != 'S') {
        return 0;
    }

    const Point opposite_corner = get_opposite_corner(corner);
    point = add_points(current, &opposite_corner);
    if (is_out_of_bounds(size, &point)) {
        return 0;
    }

    const char value2 = get_value_at_point(table, size, &point);
    if (value2 != 'M' && value2 != 'S' || value1 == value2) {
        return 0;
    }

    return 1;
}

static int has_cross(char **table, const TableSize *size, const Point *current) {
    const Point upper_corners[] = {
        {-1, -1},
        {1, -1}
    };

    const unsigned long upper_corners_size = sizeof(upper_corners) / sizeof(upper_corners[0]);

    for (int i = 0; i < upper_corners_size; i++) {
        const Point corner = upper_corners[i];
        if (!has_word(table, size, current, &corner)) {
            return 0;
        }
    }
    return 1;
}

static int get_total(char **table, const TableSize *size) {
    int total = 0;
    for (int y = 0; y < size->lines; y++) {
        for (int x = 0; x < size->columns; x++) {
            const char current = table[y][x];
            if (current == 'A') {
                Point current_position = {x, y};
                total += has_cross(table, size, &current_position);
            }
        }
    }
    return total;
}

int get_answer_part2_test() {
    const TableSize size = {10, 10};
    return read_file_day04_and_return_answer("../day_04/day04_test.txt", &size, get_total);
}

int get_answer_part2() {
    const TableSize size = {140, 140};
    return read_file_day04_and_return_answer("../day_04/day04.txt", &size, get_total);
}

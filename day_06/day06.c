//
// Created by romain on 14/12/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "day06.h"
#include "../utils.h"

#include "../common/set.h"

#define EMPTY_SPACE '.'
#define OBSTRUCTION '#'

static int equals(const Point *left, const Point *right) {
    return left->x == right->x && left->y == right->y;
}

static void print_map(const int **map, const TableSize *size) {
    for (int y = 0; y < size->lines; y++) {
        for (int x = 0; x < size->columns; x++) {
            putchar(map[y][x]);
        }
        putchar('\n');
    }
    putchar('\n');
}

static void get_direction(const char agent, Point *point) {
    switch (agent) {
        case '>':
            point->x = 1;
            point->y = 0;
            break;
        case '<':
            point->x = -1;
            point->y = 0;
            break;
        case '^':
            point->x = 0;
            point->y = -1;
            break;
        case 'v':
            point->x = 0;
            point->y = 1;
            break;
        default:
            printf("Invalid direction %c", agent);
            exit(1);
    }
}

static int is_out_of_bounds(const int **map, const TableSize *size, const Point *point) {
    return point->x < 0 || point->x >= size->columns || point->y < 0 || point->y >= size->lines;
}

static char read_map(const int **map, const TableSize *size, const Point *point) {
    if (is_out_of_bounds(map, size, point)) {
        printf("Out of bounds: %d %d\n", point->x, point->y);
        exit(1);
    }
    return (char) map[point->y][point->x];
}

static void write_in_map(int **map, const TableSize *size, const Point *point, const char value) {
    if (is_out_of_bounds(map, size, point)) {
        printf("Out of bounds: %d %d\n", point->x, point->y);
        exit(1);
    }
    map[point->y][point->x] = (int) value;
}

static int is_agent(const char c) {
    return c == '>' || c == '<' || c == '^' || c == 'v';
}

static void get_agent_position(const int **map, const TableSize *size, Point *point) {
    for (int y = 0; y < size->lines; y++) {
        for (int x = 0; x < size->columns; x++) {
            Point position = {x, y};
            const char c = read_map(map, size, &position);
            if (is_agent(c)) {
                point->x = x;
                point->y = y;
                return;
            }
        }
    }
}

static void rotate_agent(char *agent) {
    switch (*agent) {
        case '>':
            *agent = 'v';
            break;
        case 'v':
            *agent = '<';
            break;
        case '<':
            *agent = '^';
            break;
        case '^':
            *agent = '>';
            break;
        default:
            printf("Invalid agent %c", *agent);
            exit(1);
    }
}

static int move_agent(int **map, const TableSize *size, const Point *current_position, Point *new_position) {
    char agent = read_map(map, size, current_position);
    Point direction;
    get_direction(agent, &direction);

    int safe = 0;

    for (int i = 0; i < 4; i++) {
        new_position->x = current_position->x + direction.x;
        new_position->y = current_position->y + direction.y;

        if (is_out_of_bounds(map, size, new_position)) {
            return 1;
        }

        const char c = read_map(map, size, new_position);
        if (c == EMPTY_SPACE) {
            safe = 1;
            break;
        }

        rotate_agent(&agent);
        get_direction(agent, &direction);
    }

    if (!safe) {
        printf("Agent %c is stuck {%d,%d}\n", agent, current_position->x, current_position->y);
        exit(1);
    }

    write_in_map(map, size, current_position, EMPTY_SPACE);
    write_in_map(map, size, new_position, agent);

    // print_map(map, size);

    return 0;
}

static void read_file_day06(const char *path, int ***map, TableSize *size) {
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

void set_day06_answer(Answer2Parts *answer) {
    const char *path = "../day_06/day06_test.txt";
    //const char *path = "../day_06/day06.txt";

    int **map_tmp = NULL;
    TableSize size = {0, 0};
    read_file_day06(path, &map_tmp, &size);
    const int **map = map_tmp;

    Point agent_position;
    get_agent_position(map, &size, &agent_position);
    int moves = 0;

    int *move_history = NULL;

    for (int i = 0; i < 10000; i++) {
        const Point current_position = agent_position;
        const int leave_area = move_agent(map, &size, &current_position, &agent_position);
        if (leave_area) {
            break;
        }

        const int code = agent_position.x * 10000 + agent_position.y;
        moves += add_set_value(&move_history, moves, code);
    }

    answer->part_1 = moves; // 5079 < correct < 5641
    answer->part_2 = 0;

    if (map_tmp != NULL) {
        for (int i = 0; i < size.lines; i++) {
            if (map_tmp[i] != NULL) {
                free(map_tmp[i]);
            }
        }
    }
}

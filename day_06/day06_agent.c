//
// Created by romain on 15/12/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "day06_agent.h"
#include "day06_map.h"

#define EMPTY_SPACE '.'
#define OBSTRUCTION '#'

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


static int is_agent(const char c) {
    return c == '>' || c == '<' || c == '^' || c == 'v';
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

void get_agent_position(const int **map, const TableSize *size, Point *point) {
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

int move_agent(int **map, const TableSize *size, const Point *current_position, Point *new_position) {
    char agent = read_map(map, size, current_position);
    Point direction;
    get_direction(agent, &direction);

    int safe = 0;

    for (int i = 0; i < 4; i++) {
        new_position->x = current_position->x + direction.x;
        new_position->y = current_position->y + direction.y;

        if (is_out_of_bounds(size, new_position)) {
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

    return 0;
}

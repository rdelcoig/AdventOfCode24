//
// Created by romain on 14/12/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "day06.h"

#include <limits.h>

#include "day06_map.h"
#include "day06_agent.h"
#include "../common/set.h"

static int encode_point(const Point *point) {
    return point->x * 10000 + point->y;
}

static void decode_point(const int code, Point *point) {
    point->x = code / 10000;
    point->y = code % 10000;
}

static void set_unique_positions(const int **map, const TableSize *size, SetInt *move_history) {
    Point agent_position;
    get_agent_position(map, size, &agent_position);

    const int max_iterations = 100000;

    for (int i = 0; i < max_iterations; i++) {
        // store the current position if not already visited
        const int code = encode_point(&agent_position);
        add_set_value(move_history, code);

        // move the agent
        const Point current_position = agent_position;
        const int leave_area = move_agent(map, size, &current_position, &agent_position);

        if (leave_area) {
            break;
        }

        if (i == max_iterations - 1) {
            printf("No solution, more steps required\n");
            exit(1);
        }

        // print_map(map, &size);
    }
}

int get_patrol_infinite_loops_count(const int **map, const TableSize *size, int *move_history) {
    Point start_agent_position;
    get_agent_position(map, size, &start_agent_position);
    const char start_direction = read_map(map, size, &start_agent_position);


    return 0;
}

void set_day06_answer(Answer2Parts *answer) {
    const char *path = "../day_06/day06_test.txt";
    // const char *path = "../day_06/day06.txt";

    int **map_tmp = NULL;
    TableSize size = {0, 0};
    read_file_day06(path, &map_tmp, &size);
    const int **map = map_tmp;

    SetInt *move_history = create_set();
    set_unique_positions(map, &size, move_history);

    if (move_history->count > INT_MAX) {
        printf("Too many moves\n");
    } else {
        answer->part_1 = (int) move_history->count;
        answer->part_2 = 0;
    }

    if (map_tmp != NULL) {
        for (int i = 0; i < size.lines; i++) {
            if (map_tmp[i] != NULL) {
                free(map_tmp[i]);
            }
        }
        free(map_tmp);
    }
    free_set(move_history);
}

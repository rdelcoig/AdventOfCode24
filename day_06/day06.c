//
// Created by romain on 14/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#include "../common/set.h"
#include "../common/utils.h"
#include "day06.h"
#include "day06_map.h"
#include "day06_agent.h"
#include "day06_agent_map.h"

#define MAX_ITERATIONS 5000

static void add_obstruction(int **map, const TableSize *size, const Point *point) {
    write_in_map(map, size, point, OBSTRUCTION);
}

static void decode_point(const int code, Point *point) {
    point->x = code / 10000;
    point->y = code % 10000;
}

static int are_array_equal(const int *array_left, const int *array_right, const int count) {
    for (int i = 0; i < count; i++) {
        if (array_left[i] != array_right[i]) {
            return 0;
        }
    }
    return 1;
}

static void set_unique_positions(const int **map, const TableSize *size, SetInt *move_history, int *infinity_loop) {
    PatrolAgent agent;
    retrieve_agent(map, size, &agent);

    *infinity_loop = 0;
    int historic_positions_count = 0;

    PatrolAgent historic_positions[MAX_ITERATIONS];

    // TODO clean correctly map - do not recopy it each time
    for (int i = 0; i < MAX_ITERATIONS; i++) {
        if (i == MAX_ITERATIONS - 1) {
            printf("No solution, more steps required \n");
            //exit(1);
        }

        const char current_direction = agent.direction;
        const Point current_position = agent.position;

        // move the agent
        int leave_area;
        int steps; // TODO remove ?
        move_agent_before_next_obstruction(map, size, &agent, &steps, &leave_area);
        add_move_history(move_history, &current_position, &agent.position);

        if (leave_area) {
            return;
        }

        // store only rotation
        if (agent.direction != current_direction) {
            historic_positions[historic_positions_count++] = agent;
        }

        // loop through history and try to find path repeat
        for (int j = 0; j < historic_positions_count - 1; j++) {
            if (equals_agent(&historic_positions[j], &historic_positions[historic_positions_count - 1])) {
                *infinity_loop = 1;
                return;
            }
        }
    }
}

static int get_patrol_infinite_loops_count(const int **map, const TableSize *size, const SetInt *move_history) {
    printf("get_patrol_infinite_loops_count %lu \n", move_history->count);

    PatrolAgent start_agent;
    retrieve_agent(map, size, &start_agent);
    const Point start_position = start_agent.position;

    Point test_position;
    int **test_map = clone_map(map, size);
    SetInt *move_history_test = create_set();

    int loop_count = 0;
    for (int round = 0; round < move_history->count; round++) {
        // get next patrol step
        const int code = move_history->values[round];
        decode_point(code, &test_position);

        // we don't set obstruction on starting point
        if (equals(&test_position, &start_position)) {
            continue;
        }

        // get map copy
        if (round > 0) {
            copy_map(map, test_map, size);
        }

        // set obstruction on test position
        write_in_map(test_map, size, &test_position, OBSTRUCTION);

        // test if infinite loop
        int infinity_loop = 0;

        clear_set(move_history_test);
        // printf("set_unique_positions round %d - obstruction %d , %d\n", round, test_position.x, test_position.y);
        set_unique_positions(test_map, size, move_history_test, &infinity_loop);

        loop_count += infinity_loop;
    }

    //free_map(&test_map, size);
    free_set(move_history_test);
    free_map(&test_map, size);
    return loop_count;
}

void set_day06_answer(Answer2Parts *answer) {
    const char *path = "../day_06/day06_test.txt";
    // const char *path = "../day_06/day06.txt";

    int **original_map = NULL;
    TableSize size = {0, 0};
    read_file_day06(path, &original_map, &size);

    const int **map = clone_map(original_map, &size);

    SetInt *move_history = create_set();
    int infinity_loop = 0;
    set_unique_positions(map, &size, move_history, &infinity_loop);

    free_map(&map, &size);

    if (move_history->count > INT_MAX) {
        printf("Too many moves\n");
    } else {
        answer->part_1 = (int) move_history->count;

        map = clone_map(original_map, &size);
        // ok < 2207
        answer->part_2 = get_patrol_infinite_loops_count(map, &size, move_history);
        free_map(&map, &size);
    }

    free_map(&original_map, &size);
    free_set(move_history);
}

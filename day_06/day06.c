//
// Created by romain on 14/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include "../common/set.h"
#include "../common/utils.h"
#include "day06.h"
#include "day06_map.h"
#include "day06_agent.h"
#include "day06_agent_map.h"

#define MAX_ITERATIONS 5000

static void set_unique_positions(MatrixMap *map, SetInt *move_history,
                                 SetInt *agent_move_history, int *infinity_loop) {
    PatrolAgent agent;
    retrieve_agent(map, &agent);
    const PatrolAgent start_agent = agent;

    if (infinity_loop != NULL) {
        *infinity_loop = 0;
    }

    for (int i = 0; i < MAX_ITERATIONS; i++) {
        if (i == MAX_ITERATIONS - 1) {
            printf("No solution, more steps required \n");
            exit(1);
        }

        const PatrolAgent current_agent = agent;

        // move the agent
        int leave_area;
        move_agent_before_next_obstruction(map, &agent, &leave_area);

        if (move_history != NULL) {
            add_move_history(move_history, &current_agent.position, &agent.position);
        }

        if (leave_area) {
            break;
        }

        if (infinity_loop != NULL) {
            if (agent_move_history != NULL) {
                *infinity_loop = !add_agent_to_set(agent_move_history, &agent);
            }

            if (*infinity_loop) {
                break;
            }
        }
    }

    set_value_in_matrix_map(map, &agent.position, EMPTY_SPACE);
    set_value_in_matrix_map(map, &start_agent.position, start_agent.direction);
}

static int get_patrol_infinite_loops_count(MatrixMap *map, const SetInt *move_history) {
    PatrolAgent start_agent;
    retrieve_agent(map, &start_agent);
    const Point start_position = start_agent.position;

    MatrixMap *test_map = clone_matrix_map(map);
    SetInt *agent_move_history = create_set_int();

    int loop_count = 0;
    for (int round = 0; round < move_history->count; round++) {
        Point past_move;
        retrieve_point_from_set(move_history, round, &past_move);

        // we don't set obstruction on starting point
        if (equals(&past_move, &start_position)) {
            continue;
        }

        // set obstruction on test position
        set_value_in_matrix_map(test_map, &past_move, OBSTRUCTION);

        // test if infinite loop
        int infinity_loop = 0;

        set_unique_positions(test_map, NULL, agent_move_history, &infinity_loop);

        clear_set_int(agent_move_history);

        loop_count += infinity_loop;

        set_value_in_matrix_map(test_map, &past_move, EMPTY_SPACE);
    }

    free_matrix_map(&test_map);
    free_set_int(agent_move_history);
    return loop_count;
}

void set_day06_answer(Answer2Parts *answer) {
    // const char *path = "../day_06/day06_test.txt";
    const char *path = "../day_06/day06.txt";

    MatrixMap *base_map = NULL;
    read_file(path, &base_map, process_file_day06);

    MatrixMap *map = clone_matrix_map(base_map);
    SetInt *move_history = create_set_int();

    set_unique_positions(map, move_history, NULL, NULL);

    if (move_history->count > INT_MAX) {
        printf("Too many moves\n");
    } else {
        answer->part_1 = (int) move_history->count;

        // reset map
        copy_matrix_map(base_map, map);

        answer->part_2 = get_patrol_infinite_loops_count(map, move_history);
    }

    free_matrix_map(&base_map);
    free_matrix_map(&map);

    free_set_int(move_history);
}

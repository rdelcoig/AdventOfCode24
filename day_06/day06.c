//
// Created by romain on 14/12/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "day06.h"
#include "day06_map.h"
#include "day06_agent.h"

#include "../common/set.h"


static int get_unique_positions(const int **map, const TableSize *size) {
    Point agent_position;
    get_agent_position(map, size, &agent_position);
    int distinct_positions = 0;

    int *move_history = NULL;
    const int max_iterations = 100000;

    for (int i = 0; i < max_iterations; i++) {
        // store the current position if not already visited
        const int code = agent_position.x * 10000 + agent_position.y;
        distinct_positions += add_set_value(&move_history, distinct_positions, code);

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
    return distinct_positions;
}

void set_day06_answer(Answer2Parts *answer) {
    // const char *path = "../day_06/day06_test.txt";
    const char *path = "../day_06/day06.txt";

    int **map_tmp = NULL;
    TableSize size = {0, 0};
    read_file_day06(path, &map_tmp, &size);
    const int **map = map_tmp;

    answer->part_1 = get_unique_positions(map, &size);
    answer->part_2 = 0;

    if (map_tmp != NULL) {
        for (int i = 0; i < size.lines; i++) {
            if (map_tmp[i] != NULL) {
                free(map_tmp[i]);
            }
        }
    }
}

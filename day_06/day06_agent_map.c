//
// Created by romain on 17/12/24.
//

#include <stdlib.h>
#include <stdio.h>

#include "../common/utils.h"
#include "day06_agent_map.h"
#include "day06_agent.h"
#include "day06_map.h"

void move_agent_in_map(int **map, const TableSize *size, const Point *current_position, const PatrolAgent *agent) {
    // move agent to next position
    write_in_map(map, size, &agent->position, agent->direction);

    // set empty space in agent previous position
    write_in_map(map, size, current_position, EMPTY_SPACE);
}

// retrieve agent from map
void retrieve_agent(const int **map, const TableSize *size, PatrolAgent *agent) {
    for (int y = 0; y < size->lines; y++) {
        for (int x = 0; x < size->columns; x++) {
            Point position = {x, y};
            const char c = read_map(map, size, &position);
            if (is_agent(c)) {
                agent->position = position;
                agent->direction = c;
                return;
            }
        }
    }

    printf("No agent found\n");
    exit(1);
}

static void set_next_step_before_obstruction(int **map, const TableSize *size, PatrolAgent *agent, int *leave_area) {
    int max;
    switch (agent->direction) {
        case AGENT_EAST:
            max = size->columns - agent->position.x;
            break;
        case AGENT_WEST:
            max = agent->position.x;
            break;
        case AGENT_NORTH:
            max = agent->position.y;
            break;
        case AGENT_SOUTH:
            max = size->lines - agent->position.y;
            break;
        default:
            printf("Invalid direction %c", agent->direction);
            exit(1);
    }

    Point agent_position = agent->position;
    Point test_position;
    get_direction(agent, &test_position);
    int i = 0;
    *leave_area = 0;
    while (i <= max) {
        Point p = add_points(&agent_position, &test_position);

        if (is_out_of_bounds(size, &p)) {
            *leave_area = 1;
            break;
        }

        if (read_map(map, size, &p) == OBSTRUCTION) {
            break;
        }

        agent_position = p;
        i++;
    }

    set_point(&agent->position, agent_position);
}

void move_agent_before_next_obstruction(int **map, const TableSize *size, PatrolAgent *agent, int *leave_area) {
    const Point position_init = agent->position;

    PatrolAgent test_agent = *agent;
    const int max_rotation_moves = 4;
    int i = 0;
    while (i < max_rotation_moves) {
        set_next_step_before_obstruction(map, size, &test_agent, leave_area);
        if (!equals(&test_agent.position, &position_init)) {
            break;
        }
        rotate_agent(&test_agent);
        i++;
    }

    if (!*leave_area && i == max_rotation_moves) {
        printf("Agent %c is stuck {%d,%d}\n", agent->direction, agent->position.x, agent->position.y);
        exit(1);
    }

    agent->direction = test_agent.direction;
    agent->position = test_agent.position;

    move_agent_in_map(map, size, &position_init, agent);
}
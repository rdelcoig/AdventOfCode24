//
// Created by romain on 15/12/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "day06_agent.h"

void get_direction(const PatrolAgent *agent, Point *point) {
    switch (agent->direction) {
        case AGENT_EAST:
            point->x = 1;
            point->y = 0;
            break;
        case AGENT_WEST:
            point->x = -1;
            point->y = 0;
            break;
        case AGENT_NORTH:
            point->x = 0;
            point->y = -1;
            break;
        case AGENT_SOUTH:
            point->x = 0;
            point->y = 1;
            break;
        default:
            printf("Invalid direction %c", agent->direction);
            exit(1);
    }
}

inline int is_agent(const char c) {
    return c == AGENT_EAST || c == AGENT_WEST || c == AGENT_NORTH || c == AGENT_SOUTH;
}

void rotate_agent(PatrolAgent *agent) {
    switch (agent->direction) {
        case AGENT_EAST:
            agent->direction = AGENT_SOUTH;
            break;
        case AGENT_SOUTH:
            agent->direction = AGENT_WEST;
            break;
        case AGENT_WEST:
            agent->direction = AGENT_NORTH;
            break;
        case AGENT_NORTH:
            agent->direction = AGENT_EAST;
            break;
        default:
            printf("Invalid agent %c", agent->direction);
            exit(1);
    }
}

int add_agent_to_set(Set *set, const PatrolAgent *agent) {
    const char *fmt = "%lu,%lu,%c";
    size_t size = snprintf(NULL, 0, fmt, agent->position.x, agent->position.y, agent->direction);
    char buffer[size + 1];
    snprintf(buffer, sizeof buffer, fmt, agent->position.x, agent->position.y, agent->direction);
    return add_set_value(set, buffer);
}

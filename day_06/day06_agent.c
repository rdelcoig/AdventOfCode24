//
// Created by romain on 15/12/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "day06_agent.h"

int is_vertical(const PatrolAgent *agent) {
    return agent->direction == AGENT_NORTH || agent->direction == AGENT_SOUTH;
}

int is_horizontal(const PatrolAgent *agent) {
    return agent->direction == AGENT_EAST || agent->direction == AGENT_WEST;
}

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

void set_next_step(const PatrolAgent *agent, Point *next_step) {
    Point direction;
    get_direction(agent, &direction);
    *next_step = add_points(&agent->position, &direction);
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

int equals_agent(const PatrolAgent *left, const PatrolAgent *right) {
    return (left == NULL && right == NULL)
           || (left != NULL
               && right != NULL
               && (left->direction == right->direction
                   && equals(&left->position, &right->position)));
}


static int encode_agent(const PatrolAgent *agent) {
    return (agent->position.x * 1000 + agent->position.y) * 1000 + (int) agent->direction;
}

static void decode_agent(const int code, PatrolAgent *agent) {
    const int x = code / 1000000;
    const int y = code / 1000 % 1000;
    const char direction = (char) (code % 1000);
    agent->position.x = x;
    agent->position.y = y;
    agent->direction = direction;
}

int add_agent_to_set(SetInt *set, const PatrolAgent *agent) {
    const int code = encode_agent(agent);
    return add_value_set_int(set, code);
}

void retrieve_agent_from_set(const SetInt *set, const int index, PatrolAgent *agent) {
    const int code = set->values[index];
    decode_agent(code, agent);
}

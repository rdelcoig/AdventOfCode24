//
// Created by romain on 15/12/24.
//

#ifndef DAY06_AGENT_H
#define DAY06_AGENT_H

#include "../common/utils.h"

#define AGENT_NORTH '^'
#define AGENT_SOUTH 'v'
#define AGENT_EAST '>'
#define AGENT_WEST '<'

typedef struct {
    Point position;
    char direction;
} PatrolAgent;

int is_vertical(const PatrolAgent *agent);

int is_horizontal(const PatrolAgent *agent);

void get_direction(const PatrolAgent *agent, Point *point);

void set_next_step(const PatrolAgent *agent, Point *next_step);

int is_agent(const char c);

void rotate_agent(PatrolAgent *agent);

int equals_agent(const PatrolAgent *left, const PatrolAgent *right);

#endif //DAY06_AGENT_H

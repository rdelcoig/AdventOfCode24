//
// Created by romain on 15/12/24.
//

#ifndef DAY06_AGENT_H
#define DAY06_AGENT_H

#include "../common/set.h"
#include "../common/point.h"

#define AGENT_NORTH '^'
#define AGENT_SOUTH 'v'
#define AGENT_EAST '>'
#define AGENT_WEST '<'

typedef struct {
    Point position;
    char direction;
} PatrolAgent;

void get_direction(const PatrolAgent *agent, Point *point);

void set_next_step(const PatrolAgent *agent, Point *next_step);

int is_agent(const char c);

void rotate_agent(PatrolAgent *agent);

int add_agent_to_set(Set *set, const PatrolAgent *agent);

#endif //DAY06_AGENT_H

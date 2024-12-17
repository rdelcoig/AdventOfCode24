//
// Created by romain on 17/12/24.
//

#ifndef DAY06_AGENT_MAP_H
#define DAY06_AGENT_MAP_H
#include "day06_agent.h"

// retrieve agent from map
void retrieve_agent(const int **map, const TableSize *size, PatrolAgent *agent);

void move_agent_before_next_obstruction(int **map, const TableSize *size, PatrolAgent *agent, int *leave_area);

#endif //DAY06_AGENT_MAP_H

//
// Created by romain on 17/12/24.
//

#ifndef DAY06_AGENT_MAP_H
#define DAY06_AGENT_MAP_H
#include "day06_agent.h"
#include "../common/matrix_map.h"

// retrieve agent from map
void retrieve_agent(const MatrixMap *map, PatrolAgent *agent) ;

void move_agent_before_next_obstruction(const MatrixMap *map, PatrolAgent *agent, int *leave_area);

#endif //DAY06_AGENT_MAP_H

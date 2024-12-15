//
// Created by romain on 15/12/24.
//

#ifndef DAY06_AGENT_H
#define DAY06_AGENT_H

#include "../common/utils.h"

void get_agent_position(const int **map, const TableSize *size, Point *point);

int move_agent(int **map, const TableSize *size, const Point *current_position, Point *new_position);

#endif //DAY06_AGENT_H

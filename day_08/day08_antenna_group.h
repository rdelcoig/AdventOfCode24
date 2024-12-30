//
// Created by romain on 27/12/24.
//

#ifndef DAY08_ANTENNA_GROUP_H
#define DAY08_ANTENNA_GROUP_H

#include "../common/matrix_map.h"
#include "../common/utils.h"

#define EMPTY_SPACE '.'
#define ANTI_NODE '#'

typedef struct {
    char frequency;
    Point *positions;
    size_t positions_size;
} AntennaGroup;

typedef struct {
    AntennaGroup **items;
    size_t count;
} AntennaGroupCollection;

AntennaGroupCollection *create_antenna_group_collection();

void free_antenna_group_collection(AntennaGroupCollection **groups);

void add_antenna(AntennaGroupCollection *groups, const char frequency, const Point position);

void write_antinodes_to_map(const PointCouple *couple, MatrixMap *map);

#endif //DAY08_ANTENNA_GROUP_H

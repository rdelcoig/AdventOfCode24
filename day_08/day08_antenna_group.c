//
// Created by romain on 27/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day08_antenna_group.h"

static AntennaGroup *create_antenna_group(const char frequency) {
    AntennaGroup *group = malloc(sizeof(AntennaGroup));
    group->frequency = frequency;
    group->positions = NULL;
    group->positions_size = 0;
    return group;
}

static void free_antenna_group(AntennaGroup *group_ptr) {
    if (group_ptr == NULL) {
        return;
    }
    free(group_ptr->positions);
    free(group_ptr);
    group_ptr = NULL;
}

static void add_antenna_position(AntennaGroup *group, const Point position) {
    if (group == NULL) {
        printf("groups is null\n");
        exit(1);
    }

    const size_t new_size = (group->positions_size + 1) * sizeof(Point);
    Point *new_positions = (Point *) realloc(group->positions, new_size);
    if (new_positions == NULL) {
        printf("Error realloc\n");
        exit(1);
    }
    group->positions = new_positions;
    group->positions[group->positions_size] = position;
    group->positions_size++;
}

static void add_antenna_group(AntennaGroupCollection *groups, const char frequency, const Point position) {
    const size_t new_count = groups->count + 1;

    AntennaGroup **new_groups = realloc(groups->items, new_count * sizeof(AntennaGroup *));
    if (new_groups == NULL) {
        printf("Error realloc\n");
        exit(1);
    }

    AntennaGroup *new_group = create_antenna_group(frequency);
    add_antenna_position(new_group, position);
    new_groups[groups->count] = new_group;

    groups->items = new_groups;
    groups->count++;
}

AntennaGroupCollection *create_antenna_group_collection() {
    AntennaGroupCollection *groups = (AntennaGroupCollection *) malloc(sizeof(AntennaGroupCollection));
    groups->items = NULL;
    groups->count = 0;
    return groups;
}

void free_antenna_group_collection(AntennaGroupCollection **groups) {
    if (*groups == NULL) {
        return;
    }
    if ((*groups)->items != NULL) {
        for (size_t i = 0; i < (*groups)->count; i++) {
            free_antenna_group((*groups)->items[i]);
        }
        free((*groups)->items);
    }
    free(*groups);
    *groups = NULL;
}

void add_antenna(AntennaGroupCollection *groups, const char frequency, const Point position) {
    if (groups == NULL) {
        printf("groups is null\n");
        exit(1);
    }

    if (groups->items == NULL) {
        add_antenna_group(groups, frequency, position);
        return;
    }

    for (size_t i = 0; i < groups->count; i++) {
        AntennaGroup *current_group = groups->items[i];
        if (current_group->frequency == frequency) {
            add_antenna_position(current_group, position);
            return;
        }
    }

    add_antenna_group(groups, frequency, position);
}

void write_antinodes_to_map(const PointCouple *couple, MatrixMap *map) {
    PointGap gap = get_point_gap(couple);

    Point antinode1_tmp = sub_gap(&couple->point1, &gap);
    Point antinode2_tmp = add_gap(&couple->point2, &gap);

    int has_value = !is_out_of_map(map, &antinode1_tmp);
    if (has_value) {
        set_value_in_matrix_map(map, &antinode1_tmp, ANTI_NODE);
    }

    has_value = !is_out_of_map(map, &antinode2_tmp);
    if (has_value) {
        set_value_in_matrix_map(map, &antinode2_tmp, ANTI_NODE);
    }
}

void write_antinodes_to_map_with_harmonics(const PointCouple *couple, MatrixMap *map) {
    const PointGap gap = get_point_gap(couple);

    Point antinode_tmp = sub_gap(&couple->point1, &gap);
    while (!is_out_of_map(map, &antinode_tmp)) {
        set_value_in_matrix_map(map, &antinode_tmp, ANTI_NODE);
        antinode_tmp = sub_gap(&antinode_tmp, &gap);
    }

    antinode_tmp = add_gap(&couple->point2, &gap);
    while (!is_out_of_map(map, &antinode_tmp)) {
        set_value_in_matrix_map(map, &antinode_tmp, ANTI_NODE);
        antinode_tmp = add_gap(&antinode_tmp, &gap);
    }

    set_value_in_matrix_map(map, &couple->point1, ANTI_NODE);
    set_value_in_matrix_map(map, &couple->point2, ANTI_NODE);
}

unsigned long count_antinodes(MatrixMap *map) {
    unsigned long antinodes_count = 0;
    for (size_t y = 0; y < map->size.lines; y++) {
        for (size_t x = 0; x < map->size.columns; x++) {
            antinodes_count += map->values[y][x] == ANTI_NODE;
        }
    }
    return antinodes_count;
}

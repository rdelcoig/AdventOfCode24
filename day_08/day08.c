//
// Created by romain on 23/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day08.h"
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

typedef struct {
    AntennaGroupCollection *group_collection;
    MatrixMap *map;
} Day08Data;

AntennaGroup *create_antenna_group(const char frequency) {
    AntennaGroup *group = malloc(sizeof(AntennaGroup));
    group->frequency = frequency;
    group->positions = NULL;
    group->positions_size = 0;
    return group;
}

void free_antenna_group(AntennaGroup *group_ptr) {
    if (group_ptr == NULL) {
        return;
    }
    free(group_ptr->positions);
    free(group_ptr);
    group_ptr = NULL;
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


int compare(const void *left, const void *right) {
    const AntennaGroup *left_ag = (AntennaGroup *) left;
    const AntennaGroup *right_ag = (AntennaGroup *) right;
    return COMPARE(left_ag->frequency, right_ag->frequency);
}

void add_antenna_position(AntennaGroup *group, const Point position) {
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

void add_antenna_group(AntennaGroupCollection *groups, const char frequency, const Point position) {
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

static void process_file_day07(FILE *file, void *data_ptr) {
    Day08Data *data = (Day08Data *) data_ptr;

    size_t columns = 0;
    size_t lines = 0;
    const int max_buffer_size = 51;
    char buffer[max_buffer_size];
    memset(buffer, 0, max_buffer_size);

    while (fgets(buffer, max_buffer_size, file)) {
        columns = strlen(buffer);
        lines++;
    }

    rewind(file);

    data->group_collection = create_antenna_group_collection();
    data->map = create_matrix_map(lines, columns);
    size_t index = 0;
    while (fgets(buffer, max_buffer_size, file)) {
        set_line_in_matrix_map(data->map, index, buffer);
        index++;
    }

    for (size_t y = 0; y < data->map->size.lines; y++) {
        for (size_t x = 0; x < data->map->size.columns; x++) {
            const char current_char = data->map->values[y][x];
            if (current_char == EMPTY_SPACE) {
                continue;
            }
            add_antenna(data->group_collection, current_char, (Point){x, y});
        }
    }
}

void set_day08_answer(Answer2Parts *answer) {
    Day08Data data;
    read_file("../day_08/day08_test.txt", &data, process_file_day07);

    // print_matrix_map(data.map);

    answer->part_1 = 0;
    answer->part_2 = 0;

    free_antenna_group_collection(&data.group_collection);
    free_matrix_map(&data.map);
}

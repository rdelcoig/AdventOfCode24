//
// Created by romain on 23/12/24.
//

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "day08.h"
#include "day08_antenna_group.h"
#include "../common/matrix_map.h"
#include "../common/utils.h"

typedef struct {
    AntennaGroupCollection *group_collection;
    MatrixMap *map;
} Day08Data;

static void process_file_day07(FILE *file, void *data_ptr) {
    Day08Data *data = (Day08Data *) data_ptr;

    size_t columns = 0;
    size_t lines = 0;
    const int max_buffer_size = 100;
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

static MatrixMap *create_antinodes_map(Day08Data *data, bool with_harmonics) {
    MatrixMap *antinodes_map = create_matrix_map(data->map->size.lines, data->map->size.columns);
    set_matrix_map(antinodes_map, EMPTY_SPACE);

    // loop through each group
    for (size_t g = 0; g < data->group_collection->count; g++) {
        AntennaGroup current_group = *data->group_collection->items[g];

        // loop through each position
        for (size_t p = 0; p < current_group.positions_size; p++) {
            Point current_point = current_group.positions[p];

            // compare with each next position to search for antinodes
            for (size_t p_next = p + 1; p_next < current_group.positions_size; p_next++) {
                Point next_point = current_group.positions[p_next];

                const PointCouple couple = {current_point, next_point};

                if (with_harmonics) {
                    write_antinodes_to_map_with_harmonics(&couple, antinodes_map);
                } else {
                    write_antinodes_to_map(&couple, antinodes_map);
                }
            }
        }
    }
    return antinodes_map;
}

void set_day08_answer(Answer2Parts *answer) {
    Day08Data data;
    // read_file("../day_08/day08_test.txt", &data, process_file_day07);
    read_file("../day_08/day08.txt", &data, process_file_day07);

    MatrixMap *antinodes_map = create_antinodes_map(&data, false);
    answer->part_1 = count_antinodes(antinodes_map);
    free_matrix_map(&antinodes_map);

    antinodes_map = create_antinodes_map(&data, true);
    answer->part_2 = count_antinodes(antinodes_map);
    free_matrix_map(&antinodes_map);

    free_antenna_group_collection(&data.group_collection);
    free_matrix_map(&data.map);
}

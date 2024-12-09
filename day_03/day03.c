//
// Created by romain on 8/12/24.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "day03.h"

#include <string.h>

#include "day03_part1.h"
#include "day03_part2.h"

static int read_file_day03(char *raw_data, const int array_size) {
    FILE *file = fopen("../day_03/day03.txt", "r");

    int i = 0;
    char c = 0;
    while ((c = (char) fgetc(file)) != EOF) {
        raw_data[i] = c;
        i++;
        if (i >= array_size) {
            i = -1;
            break;
        }
    }

    fclose(file);
    return i;
}

void set_day03_answer(Answer2Parts *answer) {
    const int memory_data_size = 100;
    char memory_data_array[memory_data_size];
    memset(memory_data_array, 0, memory_data_size);

    set_part1_test_data(memory_data_array, memory_data_size);
    answer->part_1 = get_part1_answer(memory_data_array);

    memset(memory_data_array, 0, memory_data_size);
    set_part2_test_data(memory_data_array, memory_data_size);
    answer->part_2 = get_part2_answer(memory_data_array);

    // const int array_size = 20000;
    // char *raw_data = calloc(array_size, sizeof(char));
    //
    // read_file_day03(raw_data, array_size);
    //
    // answer->part_1 = get_part1_answer(raw_data);
    // answer->part_2 = get_part2_answer(raw_data);
    //
    // free(raw_data);
}

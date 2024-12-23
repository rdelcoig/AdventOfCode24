//
// Created by romain on 8/12/24.
//

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "day03.h"
#include "day03_part1.h"
#include "day03_part2.h"

typedef struct {
    const int array_size;
    char *raw_data;
    int data_count;
} Day03Data;

static void process_file_day03(FILE *file, void *data_ptr) {
    Day03Data *data = (Day03Data *) data_ptr;
    int i = 0;
    char c = 0;
    while ((c = (char) fgetc(file)) != EOF) {
        data->raw_data[i] = c;
        i++;
        if (i >= data->array_size) {
            i = -1;
            break;
        }
    }

    data->data_count = i;
}

void set_day03_answer(Answer2Parts *answer) {
    const int array_size = 20000;

    Day03Data data = {
        array_size,
        calloc(array_size, sizeof(char)),
        0
    };

    read_file("../day_03/day03.txt", &data, process_file_day03);

    answer->part_1 = get_part1_answer(data.raw_data);
    answer->part_2 = get_part2_answer(data.raw_data);

    free(data.raw_data);
}

//
// Created by romain on 10/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#include "day04.h"

static void read_file_day04(char **raw_data, const int max_lines, const int line_length, const int test) {
    const char *path = test ? "../day_04/day04_test.txt" : "../day_04/day04.txt";
    FILE *file = fopen(path, "r");

    int i = 0;
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1 && i < max_lines) {
        strncpy(raw_data[i], line, line_length);
        i++;
    }

    fclose(file);
}

void set_day04_answer(Answer2Parts *answer) {
    const int lines_count = 10;
    const int line_length = 10;
    char *lines[lines_count];
    for (int i = 0; i < lines_count; i++) {
        lines[i] = calloc(line_length + 1, sizeof(char));
    }

    read_file_day04(lines, lines_count, line_length, 1);

    for (int i = 0; i < lines_count; i++) {
        printf("%d - %s\n", i, lines[i]);
    }

    answer->part_1 = 0;
    answer->part_2 = 0;

    for (int i = 0; i < lines_count; i++)
        free(lines[i]);
}

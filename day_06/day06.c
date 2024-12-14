//
// Created by romain on 14/12/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "day06.h"
#include "../utils.h"

void read_file_day05(const char *path, int ***map) {
    FILE *file = fopen(path, "r");

    const int size = 12;
    char line[size];
    while (fgets(line, size, file) != NULL) {
        printf("%s", line);
    }

    fclose(file);
}

void set_day05_answer(Answer2Parts *answer) {
    const char *path = "../day_06/day06_test.txt";
    //const char *path = "../day_06/day06.txt";

    int **map = NULL;

    answer->part_1 = 41;
    answer->part_2 = 0;
}

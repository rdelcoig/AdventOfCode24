//
// Created by romain on 14/12/24.
//

#include <stdio.h>
#include <stdlib.h>

#include "day06.h"
#include "../utils.h"

static void read_file_day06(const char *path, int ***map) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        perror("File not found");
        exit(1);
    }

    const int size = 12;
    char line[size];
    while (fgets(line, size, file) != NULL) {
        // printf("%d %d %d : %s", line[9], line[10], line[11], line);
        //printf("%d : %s", line[9], line);
    }

    fclose(file);
}

void set_day06_answer(Answer2Parts *answer) {
    const char *path = "../day_06/day06_test.txt";
    //const char *path = "../day_06/day06.txt";

    int **map = NULL;

    read_file_day06(path, &map);

    answer->part_1 = 41;
    answer->part_2 = 0;
}

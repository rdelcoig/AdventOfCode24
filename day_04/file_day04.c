//
// Created by romain on 10/12/24.
//

#include <stdio.h>
#include <string.h>

#include "file_day04.h"

void read_file_day04(const char *path, const TableSize *size, char **raw_data) {
    FILE *file = fopen(path, "r");

    int i = 0;
    char *line = NULL;
    size_t len = 0;
    while (getline(&line, &len, file) != -1 && i < size->lines) {
        strncpy(raw_data[i], line, size->columns);
        i++;
    }

    fclose(file);
}

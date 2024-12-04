//
// Created by romain on 4/12/24.
//

#include <stdlib.h>
#include <stdio.h>

#include "day02.h"

#define REPORTS_COUNT 1000
#define MAX_LEVELS 10
#define INITIAL_MULTIPLIER 1;
#define INCREASING(i) ((i > 0) - (i < 0))

static void readFile(int **reports) {
    FILE *file = fopen("../day_02/day02.txt", "r");

    if (file == NULL) {
        perror("Failed to open the file");
    }

    int report_index = 0;

    // read all reports
    while (!feof(file) && report_index < REPORTS_COUNT) {
        int level_index = 0;

        // read report (all levels)
        while (1) {
            int multiplier = INITIAL_MULTIPLIER;
            int currentValue = 0;
            char c = '\0';

            // read one level
            while (1) {
                c = fgetc(file);

                if (c == '\n' || c == ' ' || c == EOF)
                    break;

                if (c >= '0' && c <= '9') {
                    currentValue *= multiplier;
                    currentValue += c - '0';
                    multiplier *= 10;
                }
            }

            if (c == EOF)
                break;

            reports[report_index][level_index++] = currentValue;

            if (c == '\n') {
                report_index++;
                break;
            }
        }
    }

    fclose(file);
}

static int getPart1Answer(const int **reports) {
    int safe = 0;
    for (int i = 0; i < REPORTS_COUNT; i++) {
        const int *report = reports[i];
        if (report[0] == 0) {
            break;
        }

        int increasing = 0;
        int safe_tmp = 1;

        const int START_INDEX = 1;
        for (int j = START_INDEX; j < MAX_LEVELS; j++) {
            const int current = reports[i][j];

            if (current == 0) {
                break;
            }

            const int previous = reports[i][j - 1];
            const int difference = current - previous;

            const int increasing_tmp = INCREASING(difference);
            if (j == START_INDEX) {
                increasing = increasing_tmp;
            }

            if (increasing == 0 || increasing_tmp != increasing || abs(difference) > 3) {
                safe_tmp = 0;
                break;
            }
        }
        safe += safe_tmp;
    }
    return safe;
}

void setDay02Answer(Day02Answer *answer) {
    int **reports = malloc(REPORTS_COUNT * sizeof(int *));
    for (int i = 0; i < REPORTS_COUNT; i++) {
        reports[i] = calloc(MAX_LEVELS, sizeof(int));
    }
    readFile(reports);

    answer->part_1 = getPart1Answer(reports);
    answer->part_2 = 0;

    for (int i = 0; i < REPORTS_COUNT; i++) {
        free(reports[i]);
    }
    free(reports);
}

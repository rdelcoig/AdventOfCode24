//
// Created by romain on 4/12/24.
//

#include <stdlib.h>
#include <stdio.h>

#include "day02.h"

#define TRUE 't'
#define FALSE 'f'
#define REPORTS_COUNT 1000
#define MAX_LEVELS 10
#define INITIAL_MULTIPLIER 1;

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

void SetDay02Answer(int *answerPtr) {
    int **reports = malloc(REPORTS_COUNT * sizeof(int *));
    for (int i = 0; i < REPORTS_COUNT; i++) {
        reports[i] = calloc(MAX_LEVELS, sizeof(int));
    }
    readFile(reports);

    int *safe = answerPtr;
    for (int i = 0; i < REPORTS_COUNT; i++) {
        const int *report = reports[i];
        if (report[0] == 0) {
            break;
        }

        char is_safe = TRUE;
        int increasing = 0;

        const int START_INDEX = 1;
        for (int j = START_INDEX; j < MAX_LEVELS; j++) {
            const int current = reports[i][j];

            if (current == 0) {
                break;
            }

            const int previous = reports[i][j - 1];
            const int difference = current - previous;

            const int increasing_tmp = (difference > 0) - (difference < 0);
            if (j == START_INDEX) {
                increasing = increasing_tmp;
            }

            if (increasing == 0 || increasing_tmp != increasing || abs(difference) > 3) {
                is_safe = FALSE;
                break;
            }
        }

        if (is_safe == TRUE) {
            (*safe)++;
        }
    }

    for (int i = 0; i < REPORTS_COUNT; i++) {
        free(reports[i]);
    }
    free(reports);
}

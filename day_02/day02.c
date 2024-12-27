//
// Created by romain on 4/12/24.
//

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include "day02.h"

#define REPORTS_COUNT 1000
#define MAX_LEVELS 10
#define INITIAL_MULTIPLIER 1;
#define INCREASING(i) ((i > 0) - (i < 0))

/**
 * Read file & store to jagged array
 */
static void process_file_day02(FILE *file, void *reports_ptr) {
    int **reports = (int **) reports_ptr;
    int report_index = 0;

    // read all reports
    while (!feof(file) && report_index < REPORTS_COUNT) {
        int level_index = 0;

        // read report (all levels)
        while (1) {
            int multiplier = INITIAL_MULTIPLIER;
            int current_value = 0;
            char c = '\0';

            // read one level
            while (1) {
                c = (char) fgetc(file);

                if (c == '\n' || c == ' ' || c == EOF)
                    break;

                if (c >= '0' && c <= '9') {
                    current_value *= multiplier;
                    current_value += c - '0';
                    multiplier *= 10;
                }
            }

            if (c == EOF)
                break;

            reports[report_index][level_index++] = current_value;

            if (c == '\n') {
                report_index++;
                break;
            }
        }
    }
}

static int get_direction(const int left, const int right) {
    const int difference = right - left;
    const int direction = INCREASING(difference);

    const int offset = abs(difference);
    const int offset_ok = offset > 0 && offset <= 3;

    return offset_ok * direction;
}

static int has_bad_index(const int *report, size_t *bad_index) {
    int direction = INT_MIN;

    size_t i = 0;
    while (i < MAX_LEVELS) {
        const int current = report[i];
        const int next = report[i + 1];

        // current = last
        if (next == 0) {
            break;
        }

        const int direction_tmp = get_direction(current, next);

        if (direction == INT_MIN) {
            direction = direction_tmp;
        }

        // if ok, check next combination
        if (direction_tmp && direction_tmp == direction) {
            i++;
        } else {
            *bad_index = i;
            return 1;
        }
    }

    // if safe, return -1
    return 0;
}

int has_bad_index_with_tolerance(const int *report, const size_t bad_index, size_t *bad_index_tmp) {
    // re-try by removing previous or current or next level
    for (int j = -1; j <= 1; j++) {
        if (bad_index + j < 0 || bad_index + j >= MAX_LEVELS)
            continue;

        // copy line without test value
        int report_tmp[MAX_LEVELS] = {};
        size_t tmp_index = 0;
        for (size_t i = 0; i < MAX_LEVELS; i++) {
            if (i == bad_index + j) {
                continue;
            }
            report_tmp[tmp_index++] = report[i];
        }

        const int with_bad_index = has_bad_index(report_tmp, bad_index_tmp);

        if (!with_bad_index) {
            return 0;
        }
    }
    return 1;
}

int is_safe(const int *report, const int with_tolerance) {
    size_t bad_index;
    int with_bad_index = has_bad_index(report, &bad_index);

    if (!with_bad_index || !with_tolerance) {
        return !with_bad_index;
    }

    size_t bad_index_tmp;
    with_bad_index = has_bad_index_with_tolerance(report, bad_index, &bad_index_tmp);
    return !with_bad_index;
}

static int count_safe_reports(int **reports, const int with_tolerance) {
    if (reports == NULL)
        return 0;

    int safe = 0;
    for (size_t i = 0; i < REPORTS_COUNT; ++i) {
        const int *report = reports[i];
        const int is_end_of_reports = report[0] == 0;

        if (is_end_of_reports) {
            break;
        }

        safe += is_safe(report, with_tolerance);
    }
    return safe;
}

static int get_day02_part1_answer(int **reports) {
    return count_safe_reports(reports, 0);
}

static int get_day02_part2_answer(int **reports) {
    return count_safe_reports(reports, 1);
}

void set_day02_answer(Answer2Parts *answer) {
    int **reports = malloc(REPORTS_COUNT * sizeof(int *));
    for (size_t i = 0; i < REPORTS_COUNT; i++) {
        reports[i] = calloc(MAX_LEVELS, sizeof(int));
    }

    read_file("../day_02/day02.txt", reports, process_file_day02);

    answer->part_1 = get_day02_part1_answer(reports);
    answer->part_2 = get_day02_part2_answer(reports);

    for (size_t i = 0; i < REPORTS_COUNT; i++) {
        if (reports[i] != NULL)
            free(reports[i]);
    }
    free(reports);
}

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
 * Reads all data from the "day02.txt" file and populates the provided 2D array 'reports' with extracted values.
 *
 * @param reports A pointer to a 2D array where each row represents a report.
 */
static void read_file_day02(int **reports) {
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
            int current_value = 0;
            char c = '\0';

            // read one level
            while (1) {
                c = fgetc(file);

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

    fclose(file);
}

/**
 * Removes a level from a report by shifting all subsequent elements
 * one position to the left, starting from the specified index.
 *
 * @param report A pointer to an array representing a report.
 * @param index The index of the level to be removed from the report.
 */
static void remove_level(int *report, const int index) {
    for (int i = index; i < MAX_LEVELS - 1; i++) {
        report[i] = report[i + 1];
    }
}

/**
 * Calculates the direction of movement between two integer values.
 * Determines if the movement from 'left' to 'right' is increasing, decreasing, or stationary.
 * It only considers valid directions when the absolute difference between the values
 *     is greater than 0 and less than or equal to 3.
 *
 * @param left An integer representing the starting value.
 * @param right An integer representing the ending value.
 * @return An integer indicating the direction: 1 for increasing, -1 for decreasing, and 0 for no valid movement.
 */
static int get_direction(const int left, const int right) {
    const int difference = right - left;
    const int direction = INCREASING(difference);

    const int offset = abs(difference);
    const int offset_ok = offset > 0 && offset <= 3;

    return offset_ok * direction;
}

/**
 * Get first bad level index
 * If there are no bad level, returns -1
 *
 * @param report A pointer to an array representing a report.
 * @param skip_index Level index in report to skip. When -1, no level to skip
 */
static int get_bad_index(const int *report, const int skip_index) {
    int increasing = INT_MIN;

    int report_tmp[10] = {};
    memcpy(report_tmp, report, sizeof(int) * 10);

    if (skip_index > -1) {
        remove_level(report_tmp, skip_index);
    }

    int i = 0;
    while (i < MAX_LEVELS) {
        const int current = report_tmp[i];
        const int next = report_tmp[i + 1];

        // current = last
        if (next == 0) {
            break;
        }

        const int direction = get_direction(current, next);

        if (increasing == INT_MIN) {
            increasing = direction;
        }

        // if ok, check next combination
        if (direction && direction == increasing) {
            i++;
        } else {
            return i;
        }
    }

    // if safe, return -1
    return -1;
}

/**
 * Determines the bad index after considering a tolerance range, which allows for retrying
 * by potentially removing the current or adjacent levels from the report.
 *
 * @param report A pointer to an array representing a report.
 * @param bad_index The current index suspected to be problematic.
 * @return The corrected bad index considering tolerance, or the original bad index if no correction can be made.
 */
int get_bad_index_with_tolerance(const int *report, const int bad_index) {
    // re-try by removing previous or current or next level
    for (int j = -1; j <= 1; j++) {
        if (bad_index + j < 0 || bad_index + j >= MAX_LEVELS)
            continue;

        const int bad_index_tmp = get_bad_index(report, bad_index + j);

        if (bad_index_tmp < 0) {
            return bad_index_tmp;
        }
    }
    return bad_index;
}

/**
 * Determines if the given report is safe to use by evaluating if any inconsistent levels
 * are present, with an option to apply tolerance adjustments.
 *
 * @param report A pointer to an array representing a report.
 * @param with_tolerance An integer flag indicating whether to apply tolerance to the safety check (non-zero value to apply).
 * @return An integer value: 1 if the report is considered safe, 0 if not safe.
 */
int is_safe(const int *report, const int with_tolerance) {
    const int bad_index = get_bad_index(report, -1);

    if (with_tolerance)
        return get_bad_index_with_tolerance(report, bad_index) < 0;

    return bad_index < 0;
}

static int count_safe_reports(const int **reports, const int with_tolerance) {
    int safe = 0;
    for (int i = 0; i < REPORTS_COUNT; ++i) {
        const int *report = reports[i];
        const int is_end_of_reports = report[0] == 0;

        if (is_end_of_reports) {
            break;
        }

        safe += is_safe(report, with_tolerance);
    }
    return safe;
}

static int get_day02_part1_answer(const int **reports) {
    return count_safe_reports(reports, 0);
}

static int get_day02_part2_answer(const int **reports) {
    return count_safe_reports(reports, 1);
}

void set_day02_answer(Answer2Parts *answer) {
    int **reports = malloc(REPORTS_COUNT * sizeof(int *));
    for (int i = 0; i < REPORTS_COUNT; i++) {
        reports[i] = calloc(MAX_LEVELS, sizeof(int));
    }
    read_file_day02(reports);

    answer->part_1 = get_day02_part1_answer(reports);
    answer->part_2 = get_day02_part2_answer(reports);

    for (int i = 0; i < REPORTS_COUNT; i++) {
        free(reports[i]);
    }
    free(reports);
}

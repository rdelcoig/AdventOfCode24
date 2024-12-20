//
// Created by romain on 18/12/24.
//

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

#include "day07.h"
#include "day07_calibration.h"

static unsigned long long int parse_next_long_long(const char *buffer, const int max_size, int *length) {
    int i = 0;
    char digits_buffer[max_size];
    memset(digits_buffer, 0, max_size);
    unsigned long long int result = 0;
    while (isdigit(buffer[i]) && i < max_size) {
        digits_buffer[i] = buffer[i];
        result *= 10;
        result += (int) (digits_buffer[i] - '0');
        i++;
    }

    *length = i;
    return result;
}

static void read_file_day07(const char *path, Calibration **calib_ptr, int *calib_count) {
    FILE *file = fopen(path, "r");

    if (file == NULL) {
        printf("Error: file not found\n");
        exit(1);
    }

    *calib_count = 0;

    const int buffer_size = 50;
    char buffer[buffer_size];

    // get line
    while (fgets(buffer, buffer_size, file) != NULL) {
        // parse line each char at a time
        if (buffer[0] == '\n' || buffer[0] == '\0') {
            break;
        }

        Calibration *calibration = create_calibration();

        for (int i = 0; i < buffer_size; i++) {
            const char c = buffer[i];
            if (c == '\n' || c == '\0') {
                break;
            }

            if (i == 0) {
                int l = 0;
                calibration->total = parse_next_long_long(buffer, buffer_size, &l);
                i += l;
                continue;
            }

            if (c == ' ') {
                int l = 0;
                const int offset = i + 1;
                const unsigned long long int val = parse_next_long_long(buffer + offset, buffer_size - offset, &l);
                if (val > INT_MAX) {
                    free_calibration(&calibration);
                    fclose(file);
                    printf("Error add number\n");
                    exit(1);
                }
                if (calibration->root->value == 0) {
                    calibration->root->value = (int) val;
                } else {
                    add_children_value(calibration, (int) val);
                }
                i += l;
            }
        }

        calib_ptr[*calib_count] = calibration;
        (*calib_count)++;
    }

    fclose(file);
}

void set_day07_answer(Answer2Parts *answer) {
    const int size = 1000;
    Calibration *calibrations[size];
    memset(calibrations, 0, size * sizeof(Calibration *));
    int calib_count = 0;

    // const char *path = "../day_07/day07_test.txt";
    const char *path = "../day_07/day07.txt";

    read_file_day07(path, calibrations, &calib_count);

    unsigned long long int total = 0;
    for (int i = 0; i < calib_count; i++) {
        const Calibration *current_calibration = calibrations[i];
        const int is_valid = is_calibration_dual_valid(current_calibration);
        if (is_valid) {
            total += current_calibration->total;
        }
    }

    answer->part_1 = total;
    answer->part_2 = 0;

    for (int i = 0; i < calib_count; i++) {
        free_calibration(&calibrations[i]);
    }
}

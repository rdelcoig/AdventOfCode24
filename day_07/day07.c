//
// Created by romain on 18/12/24.
//

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "day07.h"
#include "day07_calibration.h"

typedef struct {
    Calibration **calibrations;
    int calibrations_count;
} Day07Data;

static unsigned long long parse_next_long_long(const char *buffer, const int max_size, int *length) {
    int i = 0;
    char digits_buffer[max_size];
    memset(digits_buffer, 0, max_size);
    unsigned long long result = 0;
    while (isdigit(buffer[i]) && i < max_size) {
        digits_buffer[i] = buffer[i];
        result *= 10;
        result += (int) (digits_buffer[i] - '0');
        i++;
    }

    *length = i;
    return result;
}

static void process_file_day07(FILE *file, Day07Data *data) {
    data->calibrations_count = 0;

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
                const unsigned long long val = parse_next_long_long(buffer + offset, buffer_size - offset, &l);
                if (val > INT_MAX) {
                    free_calibration(&calibration);
                    fclose(file);
                    printf("Error add number\n");
                    exit(1);
                }
                calibration->values[calibration->count++] = val;
                if (calibration->count > CALIBRATION_MAX_SIZE) {
                    printf("Error add number\n");
                    exit(1);
                }
                i += l;
            }
        }

        data->calibrations[data->calibrations_count++] = calibration;
    }
}

void set_day07_answer(Answer2Parts *answer) {
    const int size = 1000;
    Calibration *calibrations[size];
    memset(calibrations, 0, size * sizeof(Calibration *));

    // const char *path = "../day_07/day07_test.txt";
    const char *path = "../day_07/day07.txt";

    Day07Data data = {calibrations, 0};
    read_file(path, &data, process_file_day07);

    unsigned long long total_1 = 0;
    unsigned long long total_2 = 0;
    for (int i = 0; i < data.calibrations_count; i++) {
        const Calibration *current_calibration = calibrations[i];
        int is_valid = is_valid_calibration_1(current_calibration);
        if (is_valid) {
            total_1 += current_calibration->total;
        }
        is_valid = is_valid_calibration_2(current_calibration);
        if (is_valid) {
            total_2 += current_calibration->total;
        }
    }

    answer->part_1 = total_1;
    answer->part_2 = total_2;

    for (int i = 0; i < data.calibrations_count; i++) {
        free_calibration(&calibrations[i]);
    }
}

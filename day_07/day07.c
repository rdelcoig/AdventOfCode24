//
// Created by romain on 18/12/24.
//

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

#include "day07.h"

/* DAY 07 : aller de droite à gauche
 * tester si total % val = 0
 * si 0 => *
 * si pas 0 => +
 * retirer/diviser val de total et recommencer
 */

static Calibration *create_calibration() {
    const int base_array_size = 4;
    Calibration *calib = malloc(sizeof(Calibration));
    calib->total = 0;
    calib->numbers_count = 0;
    calib->numbers = malloc(sizeof(int) * base_array_size);
    calib->numbers_capacity = base_array_size;
    return calib;
}

static void free_calibration(Calibration **calib) {
    if (calib == NULL) {
        return;
    }
    if (*calib == NULL) {
        calib = NULL;
        return;
    }
    if ((*calib)->numbers != NULL) {
        free((*calib)->numbers);
        (*calib)->numbers = NULL;
    }
    free(*calib);
    calib = NULL;
}

static int add_number(Calibration *calib, const int number) {
    if (calib == NULL) {
        return 0;
    }

    if (calib->numbers_capacity <= calib->numbers_count) {
        calib->numbers_capacity *= 2;
        if (!reallocate_int_array(&calib->numbers, calib->numbers_capacity)) {
            return 0;
        }
    }
    calib->numbers[calib->numbers_count++] = number;
    return 1;
}

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
                if (val > INT_MAX || !add_number(calibration, (int) val)) {
                    free_calibration(&calibration);
                    fclose(file);
                    printf("Error add number\n");
                    exit(1);
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
    for (int i = 0; i < size; i++) {
        calibrations[i] = NULL;
    }
    int calib_count = 0;

    // const char *path = "../day_07/day07_test.txt";
    const char *path = "../day_07/day07.txt";

    read_file_day07(path, calibrations, &calib_count);

    for (int i = 0; i < calib_count; i++) {
        printf("%llu:", calibrations[i]->total);
        for (int j = 0; j < calibrations[i]->numbers_count; j++) {
            printf(" %d", calibrations[i]->numbers[j]);
        }
        printf("\n");
    }

    answer->part_1 = 0;
    answer->part_2 = 0;

    for (int i = 0; i < calib_count; i++) {
        free_calibration(&calibrations[i]);
    }
}

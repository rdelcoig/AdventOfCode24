//
// Created by romain on 20/12/24.
//

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "day07_calibration.h"

Calibration *create_calibration() {
    Calibration *calib = malloc(sizeof(Calibration));
    calib->total = 0;
    calib->count = 0;
    memset(calib->values, 0, sizeof(unsigned int) * CALIBRATION_MAX_SIZE);
    return calib;
}

void free_calibration(Calibration **calib) {
    if (*calib == NULL) {
        calib = NULL;
        return;
    }
    memset((*calib)->values, 0, sizeof(unsigned int) * CALIBRATION_MAX_SIZE);
    free(*calib);
    calib = NULL;
}

static unsigned long long concat_values(const unsigned long long value, const unsigned int next) {
    const int max_length = 20;
    char buffer[max_length];
    const int i = snprintf(buffer, max_length, "%llu%u", value, next);
    if (i > max_length) {
        printf("Error concat values\n");
        exit(1);
    }
    return (unsigned long long) strtoull(buffer, NULL, 10);
}

static int is_valid_calibration(const Calibration *calib, char *ops, const int value_index,
                                const unsigned long long result) {
    if (calib->count == value_index) {
        return result == calib->total;
    }

    int is_valid = 0;
    if (strchr(ops, '+') != NULL) {
        is_valid += is_valid_calibration(calib, ops, value_index + 1, result + calib->values[value_index]);
    }
    if (strchr(ops, '*') != NULL) {
        is_valid += is_valid_calibration(calib, ops, value_index + 1, result * calib->values[value_index]);
    }
    if (strchr(ops, '|') != NULL) {
        is_valid += is_valid_calibration(calib, ops, value_index + 1,
                                         concat_values(result, calib->values[value_index]));
    }

    return is_valid;
}

int is_valid_calibration_1(const Calibration *calib) {
    return is_valid_calibration(calib, "+*", 1, calib->values[0]);
}

int is_valid_calibration_2(const Calibration *calib) {
    return is_valid_calibration(calib, "+*||", 1, calib->values[0]);
}

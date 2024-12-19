//
// Created by romain on 18/12/24.
//

#ifndef DAY07_H
#define DAY07_H

#include "../common/utils.h"

struct calibration_node_dual {
    int value;
    char operation;
    struct calibration_node_dual *add, *mul;
};

typedef struct calibration_node_dual CalibrationNodeDual;

typedef struct {
    unsigned long long int total;
    CalibrationNodeDual *root;
} Calibration;

void set_day07_answer(Answer2Parts *answer);

#endif //DAY07_H

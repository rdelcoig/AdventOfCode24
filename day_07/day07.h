//
// Created by romain on 18/12/24.
//

#ifndef DAY07_H
#define DAY07_H

#include "../common/utils.h"

typedef struct {
    unsigned long long int total;
    int *numbers;
    int numbers_count;
    int numbers_capacity;
} Calibration;

void set_day07_answer(Answer2Parts *answer);

#endif //DAY07_H

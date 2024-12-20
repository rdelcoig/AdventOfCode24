//
// Created by romain on 20/12/24.
//

#ifndef DAY07_CALIBRATION_H
#define DAY07_CALIBRATION_H

#define CALIBRATION_MAX_SIZE 15

typedef struct {
    unsigned long long total;
    int count;
    unsigned int values[CALIBRATION_MAX_SIZE];
} Calibration;

Calibration *create_calibration();

void free_calibration(Calibration **calib);

int is_valid_calibration_1(const Calibration *calib);

int is_valid_calibration_2(const Calibration *calib);

#endif //DAY07_CALIBRATION_H

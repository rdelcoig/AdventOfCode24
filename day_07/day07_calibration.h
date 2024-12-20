//
// Created by romain on 20/12/24.
//

#ifndef DAY07_CALIBRATION_H
#define DAY07_CALIBRATION_H

struct calibration_node {
    int value;
    char operation;
    struct calibration_node *add, *mul;
};

typedef struct calibration_node CalibrationNode;

typedef struct {
    unsigned long long int total;
    CalibrationNode *root;
} Calibration;

Calibration *create_calibration();

void free_calibration(Calibration **calib);

void add_children_value(const Calibration *calibration, const int value);

int is_calibration_valid(const Calibration *calibration);

#endif //DAY07_CALIBRATION_H

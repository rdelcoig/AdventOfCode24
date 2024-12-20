//
// Created by romain on 20/12/24.
//

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>

#include "day07_calibration.h"

static CalibrationNode *create_calibration_node() {
    CalibrationNode *node = malloc(sizeof(CalibrationNode));
    node->value = 0;
    node->operation = 0;
    node->add = node->mul = NULL;
    return node;
}

static void free_calibration_node(CalibrationNode **node) {
    if (node == NULL) {
        return;
    }
    if (*node == NULL) {
        node = NULL;
        return;
    }

    if ((*node)->add != NULL) {
        free_calibration_node(&(*node)->add);
    }
    if ((*node)->mul != NULL) {
        free_calibration_node(&(*node)->mul);
    }
    free(*node);
    node = NULL;
}

static void add_child_node_value(CalibrationNode **node, const int value, const char operation) {
    CalibrationNode *node_tmp = create_calibration_node();
    node_tmp->value = value;
    node_tmp->operation = operation;
    node_tmp->add = NULL;
    node_tmp->mul = NULL;
    *node = node_tmp;
}

static void add_children(CalibrationNode *node, const int value) {
    if (node->add != NULL) {
        add_children(node->add, value);
    }

    if (node->mul != NULL) {
        add_children(node->mul, value);
    }

    if (node->add == NULL) {
        add_child_node_value(&node->add, value, '+');
    }

    if (node->mul == NULL) {
        add_child_node_value(&node->mul, value, '*');
    }
}

Calibration *create_calibration() {
    Calibration *calib = malloc(sizeof(Calibration));
    calib->total = 0;
    calib->root = create_calibration_node();
    return calib;
}

void free_calibration(Calibration **calib) {
    if (*calib == NULL) {
        calib = NULL;
        return;
    }
    if ((*calib)->root != NULL) {
        free_calibration_node(&(*calib)->root);
    }
    free(*calib);
    calib = NULL;
}

static unsigned long long int get_total_value(const CalibrationNode *calibration_ptr, const int depth,
                                              const int mask) {
    CalibrationNode current = *calibration_ptr;
    unsigned long long int value = 0;
    int mask_cmp = 1;
    for (int i = 1; i <= depth; i++) {
        if (current.operation == '+') {
            value += current.value;
        } else if (current.operation == '*') {
            value *= current.value;
        } else {
            value = current.value;
        }

        if ((mask & mask_cmp) == 0) {
            if (current.add == NULL) {
                break;
            }
            current = *current.add;
        } else {
            if (current.mul == NULL) {
                break;
            }
            current = *current.mul;
        }
        mask_cmp <<= 1;
    }
    return value;
}

void add_children_value(const Calibration *calibration, const int value) {
    add_children(calibration->root, value);
}

int is_calibration_valid(const Calibration *calibration) {
    int depth = 1;
    int mask = 2;
    CalibrationNode current = *calibration->root;
    for (int i = 0; i < 100; i++) {
        if (current.add == NULL) break;
        depth++;
        mask <<= 1;
        current = *current.add;
    }

    current = *calibration->root;
    while (mask > 0) {
        unsigned long long int value = get_total_value(&current, depth, mask);
        if (calibration->total == value) {
            return 1;
        }
        mask--;
    }
    return 0;
}


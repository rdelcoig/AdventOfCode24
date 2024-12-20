//
// Created by romain on 20/12/24.
//

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#include "day07_calibration.h"

static CalibrationNode *create_calibration_node() {
    CalibrationNode *node = malloc(sizeof(CalibrationNode));
    node->value = 0;
    memset(node->operation, 0, 3);
    node->add = node->mul = node->concat = NULL;
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
    if ((*node)->concat != NULL) {
        free_calibration_node(&(*node)->concat);
    }
    free(*node);
    node = NULL;
}

static void add_child_node_value(CalibrationNode **node, const int value, const char *operation) {
    CalibrationNode *node_tmp = create_calibration_node();
    node_tmp->value = value;
    strncpy(node_tmp->operation, operation, 2);
    node_tmp->add = node_tmp->mul = node_tmp->concat = NULL;
    *node = node_tmp;
}

static void add_children(CalibrationNode *node, const int value) {
    if (node->add == NULL) {
        add_child_node_value(&node->add, value, "+");
    } else {
        add_children(node->add, value);
    }

    if (node->mul == NULL) {
        add_child_node_value(&node->mul, value, "*");
    } else {
        add_children(node->mul, value);
    }

    if (node->concat == NULL) {
        add_child_node_value(&node->concat, value, "||");
    } else {
        add_children(node->concat, value);
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

static unsigned long long get_total_value_dual(const CalibrationNode *calibration_ptr, const unsigned short depth,
                                               const unsigned short mask) {
    CalibrationNode current = *calibration_ptr;
    unsigned long long value = 0;
    short mask_cmp = 1;
    for (int i = 1; i <= depth; i++) {
        if (strcmp(current.operation, "+") == 0) {
            value += current.value;
        } else if (strcmp(current.operation, "*") == 0) {
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

int is_calibration_dual_valid(const Calibration *calibration) {
    unsigned short depth = 1;
    unsigned short mask = 2;
    CalibrationNode current = *calibration->root;
    for (int i = 0; i < 16; i++) {
        if (current.add == NULL) break;
        depth++;
        mask <<= 1;
        current = *current.add;
    }

    current = *calibration->root;
    while (mask > 0) {
        const unsigned long long value = get_total_value_dual(&current, depth, mask);
        if (calibration->total == value) {
            return 1;
        }
        mask--;
    }
    return 0;
}

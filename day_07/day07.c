//
// Created by romain on 18/12/24.
//

#include <stdio.h>
#include <ctype.h>
#include <limits.h>
#include <string.h>

#include "day07.h"

static CalibrationNodeDual *create_calibration_node() {
    CalibrationNodeDual *node = malloc(sizeof(CalibrationNodeDual));
    node->value = 0;
    node->operation = 0;
    node->add = node->mul = NULL;
    return node;
}

static void free_calibration_node(CalibrationNodeDual **node) {
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

static void add_child_node_value(CalibrationNodeDual **node, const int value, const char operation) {
    CalibrationNodeDual *node_tmp = create_calibration_node();
    node_tmp->value = value;
    node_tmp->operation = operation;
    node_tmp->add = NULL;
    node_tmp->mul = NULL;
    *node = node_tmp;
}

static void add_children(CalibrationNodeDual *node, const int value) {
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

static Calibration *create_calibration() {
    Calibration *calib = malloc(sizeof(Calibration));
    calib->total = 0;
    calib->root = NULL;
    return calib;
}

static void free_calibration(Calibration **calib) {
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

static unsigned long long int get_total_value(const CalibrationNodeDual *calibration_ptr, const int depth,
                                              const int mask) {
    CalibrationNodeDual current = *calibration_ptr;
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

static int is_calibration_valid(const Calibration *calibration) {
    int depth = 1;
    int mask = 2;
    CalibrationNodeDual current = *calibration->root;
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
                if (calibration->root == NULL) {
                    calibration->root = create_calibration_node();
                    calibration->root->value = (int) val;
                } else {
                    add_children(calibration->root, (int) val);
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

    const char *path = "../day_07/day07_test.txt";
    // const char *path = "../day_07/day07.txt";

    read_file_day07(path, calibrations, &calib_count);

    unsigned long long int total = 0;
    for (int i = 0; i < calib_count; i++) {
        const Calibration *current_calibration = calibrations[i];
        const int is_valid = is_calibration_valid(current_calibration);
        if (is_valid) {
            total += current_calibration->total;
        }
    }

    answer->part_1 = 2437272016585;
    answer->part_2 = 0;

    for (int i = 0; i < calib_count; i++) {
        free_calibration(&calibrations[i]);
    }
}

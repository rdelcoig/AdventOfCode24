//
// Created by romain on 3/12/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day01.h"
#include "../common/utils.h"

#define ARRAY_SIZE 1000

typedef struct {
    int left_array[ARRAY_SIZE];
    int right_array[ARRAY_SIZE];
} Day01Data;

/**
 * Compare function for quick sort
 */
static int compare(const void *left, const void *right) {
    const int int_left = *(int *) left;
    const int int_right = *(int *) right;
    return COMPARE(int_left, int_right);
}

/**
 * Read day 01 file and store left and right columns in corresponding arrays
 */
static void process_file_day01(FILE *file, Day01Data *data) {
    int i = 0;

    while (fscanf(file, "%d   %d", &data->left_array[i], &data->right_array[i]) == 2 && i < ARRAY_SIZE) {
        i++;
    }
}

static int get_day01_part1_answer(const int *left_array, const int *right_array) {
    int result = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        result += abs(left_array[i] - right_array[i]);
    }

    return result;
}

static int get_day02_part2_answer(const int *left_array, const int *right_array) {
    int similarity_score = 0;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        const int current_left = left_array[i];

        int similarity_score_tmp = 0;
        for (int j = 0; j < ARRAY_SIZE; j++) {
            const int current_right = right_array[j];
            if (current_left == current_right) {
                similarity_score_tmp += current_left;
            }
            if (current_left < current_right) {
                break;
            }
        }
        similarity_score += similarity_score_tmp;
    }

    return similarity_score;
}

void set_day01_answer(Answer2Parts *answer) {
    const ulong mem_size = ARRAY_SIZE * sizeof(int);

    Day01Data data;
    read_file("../day_01/day01.txt", &data, process_file_day01);

    qsort(data.left_array, ARRAY_SIZE, sizeof(int), compare);
    qsort(data.right_array, ARRAY_SIZE, sizeof(int), compare);

    int left_array[ARRAY_SIZE];
    int right_array[ARRAY_SIZE];
    memcpy(left_array, data.left_array, mem_size);
    memcpy(right_array, data.right_array, mem_size);

    answer->part_1 = get_day01_part1_answer(left_array, right_array);

    memcpy(left_array, data.left_array, mem_size);
    memcpy(right_array, data.right_array, mem_size);

    answer->part_2 = get_day02_part2_answer(left_array, right_array);
}

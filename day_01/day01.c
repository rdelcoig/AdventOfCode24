//
// Created by romain on 3/12/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day01.h"
#include "../utils.h"

#define ARRAY_SIZE 1000

static void read_file_day01(int *left_array, int *right_array) {
    FILE *file = fopen("../day_01/day01.txt", "r");

    if (file == NULL) {
        perror("Failed to open the file");
    }

    int i = 0;

    while (fscanf(file, "%d   %d", &left_array[i], &right_array[i]) == 2 && i < ARRAY_SIZE) {
        i++;
    }

    fclose(file);

    qsort(left_array, ARRAY_SIZE, sizeof(int), compare);
    qsort(right_array, ARRAY_SIZE, sizeof(int), compare);
}

static int get_day01_part1_answer(const int *leftArray, const int *rightArray) {
    int result = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        result += abs(leftArray[i] - rightArray[i]);
    }

    return result;
}

static int get_day02_part2_answer(const int *leftArray, const int *rightArray) {
    int similarityScore = 0;

    for (int i = 0; i < ARRAY_SIZE; i++) {
        const int currentLeft = leftArray[i];

        int similarityScore_tmp = 0;
        for (int j = 0; j < ARRAY_SIZE; j++) {
            const int currentRight = rightArray[j];
            if (currentLeft == currentRight) {
                similarityScore_tmp += currentLeft;
            }
            if (currentLeft < currentRight) {
                break;
            }
        }
        similarityScore += similarityScore_tmp;
    }

    return similarityScore;
}

void set_day01_answer(Day01Answer *answer) {
    const ulong mem_size = ARRAY_SIZE * sizeof(int);

    int *left_array_1 = malloc(mem_size);
    int *right_array_1 = malloc(mem_size);

    read_file_day01(left_array_1, right_array_1);

    int *left_array_2 = malloc(mem_size);
    int *right_array_2 = malloc(mem_size);
    memcpy(left_array_2, left_array_1, mem_size);
    memcpy(right_array_2, right_array_1, mem_size);

    answer->part_1 = get_day01_part1_answer(left_array_1, right_array_1);
    answer->part_2 = get_day02_part2_answer(left_array_2, right_array_2);

    free(left_array_1);
    free(right_array_1);
    free(left_array_2);
    free(right_array_2);
}

//
// Created by romain on 3/12/24.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day01.h"
#include "../utils.h"

#define ARRAY_SIZE 1000

static void readFile(int *leftArray, int *rightArray) {
    FILE *file = fopen("../day_01/day01.txt", "r");

    if (file == NULL) {
        perror("Failed to open the file");
    }

    int i = 0;

    while (fscanf(file, "%d   %d", &leftArray[i], &rightArray[i]) == 2 && i < ARRAY_SIZE) {
        i++;
    }

    fclose(file);

    qsort(leftArray, ARRAY_SIZE, sizeof(int), compare);
    qsort(rightArray, ARRAY_SIZE, sizeof(int), compare);
}

static int getPart1Answer(const int *leftArray, const int *rightArray) {
    int result = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        result += abs(leftArray[i] - rightArray[i]);
    }

    return result;
}

static int getPart2Answer(const int *leftArray, const int *rightArray) {
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

void setDay01Answer(Day01Answer *answer) {
    const ulong MEM_SIZE = ARRAY_SIZE * sizeof(int);

    int *left_array_1 = malloc(MEM_SIZE);
    int *right_array_1 = malloc(MEM_SIZE);

    readFile(left_array_1, right_array_1);

    int *left_array_2 = malloc(MEM_SIZE);
    int *right_array_2 = malloc(MEM_SIZE);
    memcpy(left_array_2, left_array_1, MEM_SIZE);
    memcpy(right_array_2, right_array_1, MEM_SIZE);

    answer->part_1 = getPart1Answer(left_array_1, right_array_1);
    answer->part_2 = getPart2Answer(left_array_2, right_array_2);

    free(left_array_1);
    free(right_array_1);
    free(left_array_2);
    free(right_array_2);
}

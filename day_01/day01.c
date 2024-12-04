//
// Created by romain on 3/12/24.
//
#include "day01.h"
#include <stdlib.h>
#include "../utils.h"
#include <stdio.h>
#include <string.h>

void readFile(int *leftArray, int *rightArray, const int ARRAY_SIZE) {
    FILE *file = fopen("../day_01/data.txt", "r");

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

int GetPart1Answer(const int *leftArray, const int *rightArray, const int ARRAY_SIZE) {
    int result = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        result += abs(leftArray[i] - rightArray[i]);
    }

    return result;
}

int GetPart2Answer(const int *leftArray, const int *rightArray, const int ARRAY_SIZE) {
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
                j += ARRAY_SIZE;
            }
        }
        similarityScore += similarityScore_tmp;
    }

    return similarityScore;
}

void SetDay01Answer(Day01Answer *answer) {
    const int FILE_SIZE = 1000;
    const ulong MEM_SIZE = FILE_SIZE * sizeof(int);

    int *left_array_1 = malloc(MEM_SIZE);
    int *right_array_1 = malloc(MEM_SIZE);

    readFile(left_array_1, right_array_1, FILE_SIZE);

    int *left_array_2 = malloc(MEM_SIZE);
    int *right_array_2 = malloc(MEM_SIZE);
    memcpy(left_array_2, left_array_1, MEM_SIZE);
    memcpy(right_array_2, right_array_1, MEM_SIZE);

    answer->part_1 = GetPart1Answer(left_array_1, right_array_1, FILE_SIZE);
    answer->part_2 = GetPart2Answer(left_array_2, right_array_2, FILE_SIZE);

    free(left_array_1);
    free(right_array_1);
    free(left_array_2);
    free(right_array_2);
}

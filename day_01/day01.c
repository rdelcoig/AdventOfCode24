//
// Created by romain on 3/12/24.
//
#include "day01.h"
#include <stdlib.h>
#include "../utils.h"
#include <stdio.h>

void readFile(int *leftArray, int *rightArray, int arraySize) {
    FILE *file = fopen("../day_01/data.txt", "r");

    if (file == NULL) {
        perror("Failed to open the file");
    }

    int i = 0;

    while (fscanf(file, "%d   %d", &leftArray[i], &rightArray[i]) == 2 && i < arraySize) {
        i++;
    }

    fclose(file);
}

inline int GetDay01Answer() {
    const int FILE_SIZE = 1000;

    int *leftArray = malloc(sizeof(int) * FILE_SIZE);
    int *rightArray = malloc(sizeof(int) * FILE_SIZE);

    readFile(leftArray, rightArray, FILE_SIZE);

    qsort(leftArray, FILE_SIZE, sizeof(int), compare);
    qsort(rightArray, FILE_SIZE, sizeof(int), compare);

    int result = 0;
    for (int i = 0; i < FILE_SIZE; i++) {
        result += abs(leftArray[i] - rightArray[i]);
    }

    free(leftArray);
    free(rightArray);

    return result;
}

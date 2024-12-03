//
// Created by romain on 3/12/24.
//
#include "day01.h"
#include <stdlib.h>
#include "../utils.h"

inline int GetDay01Answer() {
    int leftArray[] = {3,4,2,1,3,3};
    int rightArray[] = {4,3,5,3,9,3};

    qsort(leftArray, sizeof(leftArray)/sizeof(int), sizeof(int), compare);
    qsort(rightArray, sizeof(rightArray)/sizeof(int), sizeof(int), compare);

    const int leftArraySize =  sizeof(leftArray)/sizeof(int);
    const int rightArraySize = sizeof(rightArray)/sizeof(int);

    const int arraySize = min(leftArraySize, rightArraySize);

    int result = 0;

    for (int i = 0; i < arraySize ; i++) {
        result += abs(leftArray[i] - rightArray[i]);
    }

    return result;
}
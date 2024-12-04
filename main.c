#include <stdio.h>
#include <stdlib.h>

#include "day_01/day01.h"

void printDay01Answer() {
    Day01Answer *day01Answer = malloc(sizeof(Day01Answer));
    SetDay01Answer(day01Answer);
    printf("Day 01 results\n--------------\n");
    printf("Part 1 : %d\n", day01Answer->part_1);
    printf("Part 2 : %d\n", day01Answer->part_2);
    free(day01Answer);
}

int main(void) {
    printDay01Answer();

    return 0;
}

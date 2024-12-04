#include <stdio.h>
#include <stdlib.h>

#include "day_01/day01.h"
#include "day_02/day02.h"

void printDay01Answer() {
    Day01Answer *day01Answer = malloc(sizeof(Day01Answer));
    SetDay01Answer(day01Answer);
    printf("\nDay 01 results\n--------------\n");
    printf("Part 1 : %d\n", day01Answer->part_1);
    printf("Part 2 : %d\n", day01Answer->part_2);
    free(day01Answer);
}

void printDay02Answer() {
    int answer = 0;
    SetDay02Answer(&answer);
    printf("\nDay 02 results\n--------------\n");
    printf("Answer : %d\n", answer);
}

int main(void) {
    printDay01Answer();
    printDay02Answer();

    return 0;
}

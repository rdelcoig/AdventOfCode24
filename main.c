#include <stdio.h>
#include <stdlib.h>

#include "day_01/day01.h"
#include "day_02/day02.h"

void printDay01Answer() {
    Day01Answer *day01Answer = malloc(sizeof(Day01Answer));
    setDay01Answer(day01Answer);

    printf("\nDay 01 results\n--------------\n");
    printf("Part 1 : %d\n", day01Answer->part_1);
    printf("Part 2 : %d\n", day01Answer->part_2);

    if (day01Answer->part_1 != 1879048 || day01Answer->part_2 != 21024792) {
        printf("!! TEST KO !! \n");
    }

    free(day01Answer);
}

void printDay02Answer() {
    Day02Answer *day02Answer = malloc(sizeof(Day02Answer));
    setDay02Answer(day02Answer);

    printf("\nDay 02 results\n--------------\n");
    printf("Part 1 : %d\n", day02Answer->part_1);
    printf("Part 2 : %d\n", day02Answer->part_2);

    free(day02Answer);
}

int main(void) {
    printDay01Answer();
    printDay02Answer();

    return 0;
}

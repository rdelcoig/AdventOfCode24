#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "day_01/day01.h"
#include "day_02/day02.h"

void print_day01_answer() {
    Answer2Parts *day01_answer = malloc(sizeof(Answer2Parts));
    set_day01_answer(day01_answer);

    printf("\nDay 01 results\n--------------\n");
    printf("Part 1 : %d\n", day01_answer->part_1);
    printf("Part 2 : %d\n", day01_answer->part_2);

    if (day01_answer->part_1 != 1879048 || day01_answer->part_2 != 21024792) {
        printf("01 : TEST KO ! \n");
    }

    free(day01_answer);
}

void print_day02_answer() {
    Answer2Parts *day02_answer = malloc(sizeof(Answer2Parts));
    set_day02_answer(day02_answer);

    printf("\nDay 02 results\n--------------\n");
    printf("Part 1 : %d\n", day02_answer->part_1);
    printf("Part 2 : %d\n", day02_answer->part_2);

    if (day02_answer->part_1 != 631 || day02_answer->part_2 != 665) {
        printf("02 : TEST KO ! \n");
    }

    free(day02_answer);
}

int main(void) {
    print_day01_answer();
    print_day02_answer();

    return 0;
}

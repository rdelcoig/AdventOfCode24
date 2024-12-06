//
// Created by romain on 6/12/24.
//
#include <stdio.h>

#include "control.h"

void print_answer(const Answer2Parts *answer, const int day) {
    printf("\nDay %02d results\n--------------\n", day);
    printf("Part 1 : %d\n", answer->part_1);
    printf("Part 2 : %d\n", answer->part_2);
}

static void control_2_parts(const Answer2Parts *answer, const Answer2Parts *control, const int day) {
    if (answer->part_1 != control->part_1 || answer->part_2 != control->part_2) {
        printf("%02d : TEST KO ! \n", day);
    }
}

void control_day_01(const Answer2Parts *answer) {
    const Answer2Parts control = {1879048, 21024792};
    control_2_parts(answer, &control, 1);
}

void control_day_02(const Answer2Parts *answer) {
    const Answer2Parts control = {631, 665};
    control_2_parts(answer, &control, 2);
}

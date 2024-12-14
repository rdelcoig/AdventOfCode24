//
// Created by romain on 6/12/24.
//
#include <stdio.h>

#include "control.h"

static void control_2_parts(const Answer2Parts *answer, const Answer2Parts *control) {
    if (answer->part_1 != control->part_1 || answer->part_2 != control->part_2) {
        printf("TEST KO ! {%d, %d}\n", control->part_1, control->part_2);
    }
}

void control_day_01(const Answer2Parts *answer) {
    const Answer2Parts control = {1879048, 21024792};
    control_2_parts(answer, &control);
}

void control_day_02(const Answer2Parts *answer) {
    const Answer2Parts control = {631, 665};
    control_2_parts(answer, &control);
}

void control_day_03(const Answer2Parts *answer) {
    //const Answer2Parts control = {161, 48};
    const Answer2Parts control = {175615763, 74361272};
    control_2_parts(answer, &control);
}

void control_day_04(const Answer2Parts *answer) {
    //const Answer2Parts control = {18, 9};
    const Answer2Parts control = {2358, 1737};
    control_2_parts(answer, &control);
}

void control_day_05(const Answer2Parts *answer) {
    const Answer2Parts control = {143, 123};
    // const Answer2Parts control = {5268, 0};
    control_2_parts(answer, &control);
}

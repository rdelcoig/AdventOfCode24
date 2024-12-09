#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "control.h"
#include "day_01/day01.h"
#include "day_02/day02.h"
#include "day_03/day03.h"

static void print_answer(void (*set_answer)(Answer2Parts *), void (*control_day)(const Answer2Parts *), const int day) {
    Answer2Parts answer;

    set_answer(&answer);

    printf("\nDay %02d results\n--------------\n", day);
    printf("Part 1 : %d\n", answer.part_1);
    printf("Part 2 : %d\n", answer.part_2);

    control_day(&answer);
}

int main(void) {
    //print_answer(set_day01_answer, control_day_01, 1);
    //print_answer(set_day02_answer, control_day_02, 2);
    print_answer(set_day03_answer, control_day_03, 3);

    return 0;
}

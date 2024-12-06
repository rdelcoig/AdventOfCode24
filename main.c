#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "control.h"
#include "day_01/day01.h"
#include "day_02/day02.h"

void print_day01_answer() {
    Answer2Parts *day01_answer = malloc(sizeof(Answer2Parts));

    set_day01_answer(day01_answer);

    print_answer(day01_answer, 1);
    control_day_01(day01_answer);

    free(day01_answer);
}

void print_day02_answer() {
    Answer2Parts *day02_answer = malloc(sizeof(Answer2Parts));

    set_day02_answer(day02_answer);

    print_answer(day02_answer, 2);
    control_day_02(day02_answer);

    free(day02_answer);
}

int main(void) {
    print_day01_answer();
    print_day02_answer();

    return 0;
}

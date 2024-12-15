#include <stdio.h>

#include "common/utils.h"
#include "day_01/day01.h"
#include "day_02/day02.h"
#include "day_03/day03.h"
#include "day_04/day04.h"
#include "day_05/day05.h"
#include "day_06/day06.h"

int main(void) {
    const int days = 6;

    const Answer2Parts control_answers[] = {
        {1879048, 21024792},
        {631, 665},
        {175615763, 74361272},
        {2358, 1737},
        {5268, 5799},
        {5080, 0}
    };

    Answer2Parts answers[days];
    set_day01_answer(&answers[0]);
    set_day02_answer(&answers[1]);
    set_day03_answer(&answers[2]);
    set_day04_answer(&answers[3]);
    set_day05_answer(&answers[4]);
    set_day06_answer(&answers[5]);

    for (int i = 0; i < days; i++) {
        const int day = i + 1;
        const Answer2Parts answer = answers[i];
        printf("\nDay %02d results\n--------------\n", day);
        printf("Part 1 : %d\n", answer.part_1);
        printf("Part 2 : %d\n", answer.part_2);

        const Answer2Parts control = control_answers[i];
        if (answer.part_1 != control.part_1 || answer.part_2 != control.part_2) {
            printf("TEST KO ! {%d, %d}\n", control.part_1, control.part_2);
        }
    }

    return 0;
}

#include <limits.h>
#include <stdio.h>
#include <time.h>

#include "common/utils.h"
#include "day_01/day01.h"
#include "day_02/day02.h"
#include "day_03/day03.h"
#include "day_04/day04.h"
#include "day_05/day05.h"
#include "day_06/day06.h"
#include "day_07/day07.h"

int main(void) {
    const int days = 7;

    const Answer2Parts control_answers[] = {
        {1879048, 21024792},
        {631, 665},
        {175615763, 74361272},
        {2358, 1737},
        {5268, 5799},
        {5080, 1919},
        {2437272016585, 162987117690649}
    };

    void (*calls[days])(Answer2Parts *);
    for (size_t i = 0; i < days; i++) {
        calls[i] = NULL;
    }

    calls[0] = set_day01_answer;
    calls[1] = set_day02_answer;
    calls[2] = set_day03_answer;
    calls[3] = set_day04_answer;
    calls[4] = set_day05_answer;
    calls[5] = set_day06_answer;
    calls[6] = set_day07_answer;

    const int start = days - days; // set n last answers to show here
    for (size_t i = start; i < days; i++) {
        if (calls[i] == NULL) {
            continue;
        }

        Answer2Parts answer;
        calls[i](&answer);

        const int day = i + 1;
        printf("\nDay %02d results\n--------------\n", day);
        printf("Part 1 : %llu\n", answer.part_1);
        printf("Part 2 : %llu\n", answer.part_2);

        const Answer2Parts control = control_answers[i];
        if (answer.part_1 != control.part_1 || answer.part_2 != control.part_2) {
            printf("TEST KO ! {%llu, %llu}\n", control.part_1, control.part_2);
        }
    }

    return 0;
}

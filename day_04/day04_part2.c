//
// Created by romain on 10/12/24.
//

#include "day04_part2.h"
#include "day04_utils.h"
#include "../utils.h"

static int get_total(char **lines, const TableSize *size) {
    return 0;
}

int get_answer_part2_test() {
    const TableSize size = {10, 10};
    return read_file_day04_and_return_answer("../day_04/day04_test.txt", &size, get_total);
}

int get_answer_part2() {
    const TableSize size = {140, 140};
    return read_file_day04_and_return_answer("../day_04/day04.txt", &size, get_total);
}

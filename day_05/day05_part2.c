//
// Created by romain on 13/12/24.
//

#include <stdlib.h>

#include "day05_part2.h"
#include "day05_utils.h"

static void set_correct_updates(const int *updates[], const int updates_count,
                                const PageRule *rules, const int rules_count,
                                const int *correct_updates[], int *correct_updates_count) {
    int correct_updates_index = 0;
    for (int i = 0; i < updates_count; i++) {
        correct_updates[i] = NULL;

        if (!is_day05_update_correct(updates[i], rules, rules_count)) {
            // TODO copy line + reorder to match rules

            correct_updates[correct_updates_index] = updates[i];
            correct_updates_index++;
        }
    }
    *correct_updates_count = correct_updates_index;
}

static int read_file_and_return_answer(const int rules_count, const int updates_count,
                                       const char *file_path) {
    PageRule rules[rules_count];

    int *updates[updates_count];
    for (int i = 0; i < updates_count; i++) {
        updates[i] = malloc(UPDATE_MAX_COUNT * sizeof(int));
        for (int j = 0; j < UPDATE_MAX_COUNT; j++) {
            updates[i][j] = -1;
        }
    }

    read_file_day05(file_path, rules, updates);

    const int correct_updates[updates_count];
    int correct_updates_count;
    set_correct_updates(updates, updates_count, rules, rules_count, correct_updates, &correct_updates_count);

    const int total = get_day05_total(correct_updates, correct_updates_count);

    for (int i = 0; i < updates_count; i++) {
        free(updates[i]);
    }

    return total;
}

int get_answer_day05_part2_test() {
    return read_file_and_return_answer(21, 6, "../day_05/day05_test.txt");
}

int get_answer_day05_part2() {
    return read_file_and_return_answer(1176, 204, "../day_05/day05.txt");
}

//
// Created by romain on 11/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day05_part1.h"
#include "day05_utils.h"

static void filter_rules_by_before(const int page, const PageRule *rules, const int rules_count,
                                   int pages_after[]) {
    int pages_after_count = 0;
    for (int i = 0; i < rules_count; i++) {
        // ensure that allocated memory is clean
        pages_after[i] = -1;

        const int current = rules[i].before;

        if (current == page) {
            // current rule matches => copy pointer to collection
            pages_after[pages_after_count] = rules[i].after;
            pages_after_count++;
        }
    }
}

static int is_update_correct(const int updates[], const PageRule *rules, const int rules_count) {
    // inspect each page
    for (int i = 0; i < UPDATE_MAX_COUNT; i++) {
        const int current_page = updates[i];

        if (current_page < 0) {
            break;
        }

        // get rules for current page (before == page)
        int pages_after[rules_count];
        filter_rules_by_before(current_page, rules, rules_count, pages_after);

        // inspect each rules
        for (int j = 0; j < rules_count; j++) {
            const int page_after = pages_after[j];

            if (page_after == -1) {
                break;
            }

            // check if a previous page is supposed to be after
            for (int k = 0; k < i; k++) {
                if (page_after == updates[k]) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

static void set_correct_updates(const int *updates[], const int updates_count,
                                const PageRule *rules, const int rules_count,
                                const int *correct_updates[], int *correct_updates_count) {
    int correct_updates_index = 0;
    for (int i = 0; i < updates_count; i++) {
        correct_updates[i] = NULL;

        if (is_update_correct(updates[i], rules, rules_count)) {
            correct_updates[correct_updates_index] = updates[i];
            correct_updates_index++;
        }
    }
    *correct_updates_count = correct_updates_index;
}

static int get_middle_value(const int updates_line[]) {
    int count = 0;
    while (count < UPDATE_MAX_COUNT) {
        if (updates_line[count] < 0) {
            break;
        }

        count++;
    }

    const int mid = count / 2;
    return updates_line[mid];
}

static int get_total(const int *updates[], const int updates_count) {
    int total = 0;
    for (int i = 0; i < updates_count; i++) {
        const int *current = updates[i];

        if (current == NULL) {
            break;
        }

        const int middle_value = get_middle_value(current);
        total += middle_value;
    }

    return total;
}

static int read_file_day05_and_return_answer(const int rules_count, const int updates_count,
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

    const int total = get_total(correct_updates, correct_updates_count);

    for (int i = 0; i < updates_count; i++) {
        free(updates[i]);
    }

    return total;
}

int get_answer_day05_part1_test() {
    return read_file_day05_and_return_answer(21, 6, "../day_05/day05_test.txt");
}

int get_answer_day05_part1() {
    return read_file_day05_and_return_answer(1176, 204, "../day_05/day05.txt");
}

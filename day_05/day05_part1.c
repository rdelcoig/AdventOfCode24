//
// Created by romain on 11/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day05_part1.h"
#include "day05_utils.h"

static void filter_rules_by_before(const int page, const PageRule *rules, const int rules_count,
                                   const PageRule **filtered_rules, int *filtered_rules_count) {
    *filtered_rules_count = 0;
    for (int i = 0; i < rules_count; i++) {
        const int current = rules[i].before;

        if (current > page) {
            return;
        }

        if (current == page) {
            // current rule matches => copy pointer to collection
            const int filtered_rules_index = *filtered_rules_count;

            filtered_rules[filtered_rules_index] = &rules[i];

            (*filtered_rules_count)++;
        }
    }
}

static int is_update_correct(const int **updates, const PageRule *rules, const int rules_count, const int index) {
    const int *line = updates[index];

    if (line[0] == -1) {
        return 0;
    }

    for (int i = 0; i < UPDATE_MAX_COUNT; i++) {
        const int current = line[i];

        const PageRule *filtered_rules[rules_count];
        int filtered_rules_count = 0;
        filter_rules_by_before(current, rules, rules_count, filtered_rules, &filtered_rules_count);

        for (int j = 0; j < filtered_rules_count; j++) {
            const PageRule *rule = filtered_rules[j];

            // go backward and check if previous aren't supposed to be after
            for (int k = i - 1; k >= 0; k--) {
                if (line[k] == rule->after) {
                    return 0;
                }
            }
        }
    }
    return 1;
}

static void set_correct_updates(const int **updates, const int updates_count,
                                const PageRule *rules, const int rules_count,
                                const int **correct_updates) {
    int correct_updates_index = 0;
    for (int i = 0; i < updates_count; i++) {
        const int *current = updates[i];

        if (is_update_correct(updates, rules, rules_count, i)) {
            // current update is correct => copy pointer to collection
            correct_updates[correct_updates_index++] = current;
        }
    }
}

static int get_total(const int **updates, const int updates_count) {
    int total = 0;
    for (int i = 0; updates[i] != NULL && i < updates_count; i++) {
        const int *current = updates[i];

        int count = 0;
        while (current[count] != -1 && count < UPDATE_MAX_COUNT) {
            count++;
        }

        const int mid = (count - 1) / 2;
        total += current[mid];
    }

    return total;
}

int get_answer_day05_part1_test() {
    const int rules_count = 21;
    const int updates_count = 6;

    PageRule rules[rules_count];

    int *updates[updates_count];
    for (int i = 0; i < updates_count; i++) {
        updates[i] = malloc(UPDATE_MAX_COUNT * sizeof(int));
        for (int j = 0; j < UPDATE_MAX_COUNT; j++) {
            updates[i][j] = -1;
        }
    }

    int *correct_updates[updates_count];
    for (int i = 0; i < updates_count; i++) {
        correct_updates[i] = NULL;
    }

    read_file_day05("../day_05/day05_test.txt", rules, updates);

    qsort(rules, rules_count, sizeof(PageRule), compare_page_rules_before_after);

    set_correct_updates(updates, updates_count, rules, rules_count, correct_updates);

    const int total = get_total(correct_updates, updates_count);

    for (int i = 0; i < updates_count; i++) {
        free(updates[i]);
    }

    return total;
}

int get_answer_day05_part1() {
    return 0;
}

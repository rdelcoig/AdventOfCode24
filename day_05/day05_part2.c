//
// Created by romain on 13/12/24.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "day05_part2.h"
#include "day05_utils.h"

static int rules_count;
static PageRule *rules;

static int updates_count;
static int **updates;

static PageRule *search_page_rule(const int a, const int b) {
    for (int i = 0; i < rules_count; i++) {
        PageRule *rule = &rules[i];
        if ((rule->before == a && rule->after == b)
            || (rule->before == b && rule->after == a)) {
            return rule;
        }
    }
    return NULL;
}

static void swap_order(int updates[], const int idx_left, const int idx_right) {
    const int left = updates[idx_left];
    const int right = updates[idx_right];
    const PageRule *rule = search_page_rule(left, right);
    if (rule != NULL && rule->after == left) {
        const int tmp = updates[idx_left];
        updates[idx_left] = updates[idx_right];
        updates[idx_right] = tmp;
    }
}

static void set_reordered_updates(int **reordered_updates, int *reordered_updates_count) {
    int reordered_updates_index = 0;
    for (int i = 0; i < updates_count; i++) {
        if (!is_day05_update_correct(updates[i], rules, rules_count)) {
            int updates_tmp[UPDATE_MAX_COUNT];
            memcpy(updates_tmp, updates[i], UPDATE_MAX_COUNT * sizeof(int));

            for (int idx_left = 0; idx_left < UPDATE_MAX_COUNT; idx_left++) {
                for (int idx_right = idx_left + 1; idx_right < UPDATE_MAX_COUNT; idx_right++) {
                    swap_order(updates_tmp, idx_left, idx_right);
                }
            }

            int **tmp = realloc(reordered_updates, (reordered_updates_index + 1) * sizeof(int *));
            if (tmp == NULL) {
                perror("Out of memory");
                free(reordered_updates);
                exit(1);
            }

            reordered_updates = tmp;
            reordered_updates[reordered_updates_index] = malloc(UPDATE_MAX_COUNT * sizeof(int));
            memcpy(reordered_updates[reordered_updates_index], updates_tmp, UPDATE_MAX_COUNT * sizeof(int));
            reordered_updates_index++;
        }
    }
    *reordered_updates_count = reordered_updates_index;
}

static int read_file_and_return_answer(const char *file_path) {
    rules = malloc(rules_count * sizeof(PageRule));
    updates = malloc(updates_count * sizeof(int *));

    for (int i = 0; i < updates_count; i++) {
        updates[i] = malloc(UPDATE_MAX_COUNT * sizeof(int));
        for (int j = 0; j < UPDATE_MAX_COUNT; j++) {
            updates[i][j] = -1;
        }
    }

    read_file_day05(file_path, rules, updates);

    int **reordered_updates = malloc(0 * sizeof(int *));
    int reordered_updates_count;
    set_reordered_updates(reordered_updates, &reordered_updates_count);

    const int total = get_day05_total(reordered_updates, reordered_updates_count);

    if (reordered_updates != NULL) {
        for (int i = 0; i < reordered_updates_count; i++) {
            free(reordered_updates[i]);
        }
        free(reordered_updates);
    }

    for (int i = 0; i < updates_count; i++) {
        free(updates[i]);
    }
    free(updates);

    free(rules);

    return total;
}

int get_answer_day05_part2_test() {
    rules_count = 21;
    updates_count = 6;
    return read_file_and_return_answer("../day_05/day05_test.txt");
}

int get_answer_day05_part2() {
    rules_count = 1176;
    updates_count = 204;
    return read_file_and_return_answer("../day_05/day05.txt");
}

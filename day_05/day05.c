//
// Created by romain on 11/12/24.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "day05.h"
#include "day05_utils.h"

static int rules_compare(const void *left, const void *right) {
    const PageRule pr_left = *(PageRule *) left;
    const PageRule pr_right = *(PageRule *) right;
    const int before_compare = COMPARE(pr_left.before, pr_right.before);
    if (before_compare)
        return before_compare;
    return COMPARE(pr_left.after, pr_right.after);
}

static int search_page_rule(const int a, const int b,
                            PageRule **rules, const int rules_count,
                            PageRule *rule_to_return) {
    PageRule test_rule = {a, b};
    const PageRule *result = bsearch(&test_rule, *rules, rules_count, sizeof(PageRule), rules_compare);

    if (result) {
        *rule_to_return = *result;
        return 1;
    }

    // when not found, swap parameters and search again

    test_rule.before = b;
    test_rule.after = a;
    result = bsearch(&test_rule, *rules, rules_count, sizeof(PageRule), rules_compare);

    if (result) {
        *rule_to_return = *result;
        return 1;
    }

    rule_to_return = NULL;
    return 0;
}

static int set_order(int **updates, const int idx_left, const int idx_right,
                     PageRule *rules, const int rules_count) {
    const int left = (*updates)[idx_left];
    const int right = (*updates)[idx_right];

    PageRule rule;
    const int found = search_page_rule(left, right, &rules, rules_count, &rule);

    if (found && rule.after == left) {
        const int tmp = (*updates)[idx_left];
        (*updates)[idx_left] = (*updates)[idx_right];
        (*updates)[idx_right] = tmp;
        return 1;
    }
    return 0;
}

static void reorder_updates(int ***unordered_updates, const int updates_count,
                            PageRule *rules, const int rules_count) {
    // for each line
    for (size_t i = 0; i < updates_count; i++) {
        int *updates_line = (*unordered_updates)[i];
        if (updates_line == NULL) {
            break;
        }

        // for each page
        for (size_t j = 0; j < UPDATE_MAX_COUNT && updates_line[j] > -1; j++) {
            // test each previous page with current
            for (size_t k = 0; k < j; k++) {
                set_order(&updates_line, k, j, rules, rules_count);
            }
        }
    }
}

static void separate_updates(int ***updates, const int updates_count,
                             PageRule **rules, const int rules_count,
                             int ***correct_updates, int *correct_updates_count,
                             int ***incorrect_updates, int *incorrect_updates_count) {
    *correct_updates_count = 0;
    *incorrect_updates_count = 0;
    for (size_t i = 0; i < updates_count; i++) {
        int *updates_line = (*updates)[i];
        if (is_day05_update_correct(updates_line, rules, rules_count)) {
            if (!reallocate_updates(correct_updates, *correct_updates_count + 1)) {
                perror("Reallocate correct_updates error");
                exit(1);
            }
            *(*correct_updates + *correct_updates_count) = updates_line;
            (*correct_updates_count)++;
        } else {
            if (!reallocate_updates(incorrect_updates, *incorrect_updates_count + 1)) {
                perror("Reallocate incorrect_updates error");
                exit(1);
            }

            *(*incorrect_updates + *incorrect_updates_count) = updates_line;
            (*incorrect_updates_count)++;
        }
    }
}

void set_day05_answer(Answer2Parts *answer) {
    //const char *path = "../day_05/day05_test.txt";
    const char *path = "../day_05/day05.txt";

    Day05Data data = {NULL, 0,NULL, 0};
    read_file(path, &data, process_file_day05);

    qsort(data.rules, data.rules_count, sizeof(PageRule), rules_compare);

    int **correct_updates = NULL;
    int **incorrect_updates = NULL;
    int correct_updates_count, incorrect_updates_count;

    separate_updates(&data.updates, data.updates_count, &data.rules, data.rules_count,
                     &correct_updates, &correct_updates_count,
                     &incorrect_updates, &incorrect_updates_count);

    reorder_updates(&incorrect_updates, incorrect_updates_count, data.rules, data.rules_count);

    answer->part_1 = get_day05_total(correct_updates, correct_updates_count);
    answer->part_2 = get_day05_total(incorrect_updates, incorrect_updates_count);

    if (data.updates != NULL) {
        for (size_t i = 0; i < data.updates_count; i++) {
            int *current = data.updates[i];
            if (current != NULL) {
                free(current);
            }
        }
        free(data.updates);
    }

    if (correct_updates != NULL) {
        // items have already been freed
        free(correct_updates);
    }

    if (incorrect_updates != NULL) {
        // items have already been freed
        free(incorrect_updates);
    }

    if (data.rules != NULL) {
        free(data.rules);
    }
}

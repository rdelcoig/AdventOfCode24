//
// Created by romain on 11/12/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day05_utils.h"
#include "../utils.h"

// int compare_page_rules_before_after(const void *left, const void *right) {
//     const PageRule pr_left = *(PageRule *) left;
//     const PageRule pr_right = *(PageRule *) right;
//     const int before_compare = COMPARE(pr_left.before, pr_right.before);
//     if (before_compare)
//         return before_compare;
//     return COMPARE(pr_left.after, pr_right.after);
// }

// int compare_page_rules_after_before(const void *left, const void *right) {
//     const PageRule pr_left = *(PageRule *) left;
//     const PageRule pr_right = *(PageRule *) right;
//     const int after_compare = COMPARE(pr_left.after, pr_right.after);
//     if (after_compare)
//         return after_compare;
//     return COMPARE(pr_left.before, pr_right.before);
// }

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

int is_day05_update_correct(const int updates[], const PageRule *rules, const int rules_count) {
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

int get_day05_total(const int *updates[], const int updates_count) {
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

void read_file_day05(const char *path, PageRule *rules, int *updates[]) {
    FILE *file = fopen(path, "r");

    int i = 0;

    const char line_1_delimiter = '|';
    const int line_1_max_length = RULE_LINE_MAX_SIZE + 2; // 2 digits + delimiter + 2 digits + line feed + null pointer
    char line_1[line_1_max_length];
    while (fgets(line_1, line_1_max_length, file) != NULL) {
        if (line_1[0] == '\n')
            break;

        char number[2];
        strncpy(number, line_1, 2);
        const int left = atoi(number);
        strncpy(number, line_1 + 3, 2);
        const int right = atoi(number);

        const PageRule pr = {left, right};
        rules[i] = pr;
        memset(line_1, 0, line_1_max_length);

        i++;
    }

    i = 0;

    const char file_part2_delimiter = ',';
    const int line_2_max_length = 70;
    char line_2[line_2_max_length];
    while (fgets(line_2, line_2_max_length, file) != NULL) {
        const char *token = strtok(line_2, &file_part2_delimiter);

        int j = 0;
        while (token) {
            updates[i][j] = atoi(token);
            token = strtok(NULL, &file_part2_delimiter);
            j++;
        }

        i++;
    }

    fclose(file);
}

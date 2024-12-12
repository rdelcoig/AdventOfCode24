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

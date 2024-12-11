//
// Created by romain on 11/12/24.
//

#ifndef DAY05_UTILS_H
#define DAY05_UTILS_H

#define RULE_LINE_MAX_SIZE 5
#define UPDATE_MAX_COUNT 25

typedef struct {
    int before;
    int after;
} PageRule;

int compare_page_rules_before_after(const void *left, const void *right);

int compare_page_rules_after_before(const void *left, const void *right);

void read_file_day05(const char *path, PageRule *rules, int **updates);

#endif //DAY05_UTILS_H

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

typedef struct {
    PageRule *rules;
    int rules_count;
    int **updates;
    int updates_count;
} Day05Data;

int reallocate_updates(int ***updates, const int updates_count);

int reallocate_updates_line(int **updates_line, const int updates_count);

void process_file_day05(FILE *file, void *data);

int is_day05_update_correct(const int *updates_line, const PageRule **rules, const int rules_count);

int get_day05_total(const int *updates[], const int updates_count);

#endif //DAY05_UTILS_H

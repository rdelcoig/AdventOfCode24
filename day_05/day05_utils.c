//
// Created by romain on 11/12/24.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "day05_utils.h"

static int reallocate_int(int **array, const int array_size) {
    int *new_array = realloc(*array, array_size * sizeof(int));
    if (new_array == NULL) {
        perror("Out of memory");
        return 0;
    }
    *array = new_array;
    return 1;
}

static int add_value_to_array(int **array, const int array_size, const int value) {
    if (!reallocate_int(array, array_size + 1)) {
        return 0;
    }
    (*array)[array_size] = value;
    return 1;
}

static void filter_rules_by_before(const int page, const PageRule **rules, const int rules_count, int **pages_after) {
    int pages_after_count = 0;

    for (size_t i = 0; i < rules_count; i++) {
        const PageRule current = (*rules)[i];

        if (current.before == page) {
            if (!add_value_to_array(pages_after, pages_after_count, current.after)) {
                perror("Reallocate pages after error");
                exit(1);
            }
            pages_after_count++;
        }

        add_value_to_array(pages_after, pages_after_count, -1);
    }
}

static int get_middle_value(const int *updates_line) {
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

int is_day05_update_correct(const int *updates_line, const PageRule **rules, const int rules_count) {
    int found_page = 0;
    int update_index = 1;
    while (*(updates_line + update_index) > -1) {
        const int current_page = *(updates_line + update_index);
        // get rules for current page (before == page)
        int *pages_after = NULL;
        filter_rules_by_before(current_page, rules, rules_count, &pages_after);

        for (size_t i = 0; i < rules_count; i++) {
            const int current_page_after = *(pages_after + i);
            if (current_page_after <= -1) {
                break;
            }

            // check if a previous page is supposed to be after
            const int *previous_page = updates_line + update_index - 1;
            while (previous_page >= updates_line) {
                if (*previous_page == current_page_after) {
                    found_page = 1;
                    break;
                }
                previous_page--;
            }

            if (found_page) {
                break;
            }
        }

        free(pages_after);
        if (found_page) {
            break;
        }
        update_index++;
    }
    return !found_page;
}

int get_day05_total(const int **updates, const int updates_count) {
    int total = 0;
    for (size_t i = 0; i < updates_count; i++) {
        const int *current = updates[i];

        if (current == NULL) {
            break;
        }

        const int middle_value = get_middle_value(current);
        total += middle_value;
    }

    return total;
}

static int reallocate_rules(PageRule **rules, const int rules_count) {
    PageRule *new_rules = realloc(*rules, rules_count * sizeof(PageRule *));
    if (new_rules == NULL) {
        perror("Out of memory");
        return 0;
    }
    *rules = new_rules;
    return 1;
}

int reallocate_updates(int ***updates, const int updates_count) {
    int **new_updates = realloc(*updates, updates_count * sizeof(int *));
    if (new_updates == NULL) {
        perror("Out of memory");
        return 0;
    }
    *updates = new_updates;
    return 1;
}

int reallocate_updates_line(int **updates_line, const int updates_count) {
    int *new_updates = realloc(*updates_line, updates_count * sizeof(int *));
    if (new_updates == NULL) {
        perror("Out of memory");
        return 0;
    }
    *updates_line = new_updates;
    return 1;
}

void process_file_day05(FILE *file, void *data_ptr) {
    Day05Data *data = (void *) data_ptr;
    int i = 0;

    int left, right;
    while (fscanf(file, "%d|%d\n", &left, &right) == 2) {
        const PageRule pr = {left, right};
        if (!reallocate_rules(&data->rules, i + 1)) {
            perror("Reallocate rules error");
            exit(1);
        }
        data->rules[i++] = pr;
    }
    data->rules_count = i;

    // go back 2 chars because of last fscanf
    fseek(file, -2, SEEK_CUR);

    i = 0;

    const char file_part2_delimiter = ',';
    const int line_2_max_length = 70;
    char line_2[line_2_max_length];
    while (fgets(line_2, line_2_max_length, file) != NULL) {
        const char *token = strtok(line_2, &file_part2_delimiter);

        int *updates_line = NULL;
        int j = 0;
        while (token) {
            if (!reallocate_updates_line(&updates_line, j + 1)) {
                perror("Reallocate updates line error");
                exit(1);
            }
            updates_line[j] = atoi(token);
            token = strtok(NULL, &file_part2_delimiter);
            j++;
        }

        if (!reallocate_updates_line(&updates_line, j + 1)) {
            perror("Reallocate updates line error");
            exit(1);
        }
        updates_line[j] = -1;

        if (!reallocate_updates(&data->updates, i + 1)) {
            perror("Reallocate updates error");
            exit(1);
        }

        data->updates[i++] = updates_line;
    }
    data->updates_count = i;
}

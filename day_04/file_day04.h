//
// Created by romain on 10/12/24.
//

#ifndef FILE_DAY04_H
#define FILE_DAY04_H

#include "../utils.h"

void read_file_day04(const char *path, const TableSize *size, char **raw_data);

int read_file_day04_and_return_answer(const char *file_path, const TableSize *size,
                                      int (*get_total)(char **lines, const TableSize *size));

#endif //FILE_DAY04_H

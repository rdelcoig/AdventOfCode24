//
// Created by romain on 9/12/24.
//

#include <stdio.h>
#include <string.h>

#include "day03_part2.h"
#include "instruction.h"

void set_part2_test_data(char *memory_data_array, const int array_size) {
    const char *str = "xmul(2,4)&mul[3,7]!^don't()_mul(5,5)+mul(32,64](mul(11,8)undo()?mul(8,5))";

    if (strlen(str) > array_size) {
        printf("array size too small \n");
        return;
    }

    strcpy(memory_data_array, str);
}

int get_part2_answer(const char *memory_data_array) {
    int total = 0;
    int skip_next_instruction = 0;
    for (size_t i = 0; i < strlen(memory_data_array); i++) {
        const char current = memory_data_array[i];

        if (current != 'm' && current != 'd') {
            continue;
        }
        char substring[MAX_INSTRUCTION_SIZE + 1];
        strncpy(substring, memory_data_array + i, MAX_INSTRUCTION_SIZE);
        substring[MAX_INSTRUCTION_SIZE] = 0;

        Instruction instruction;
        const int is_parsed = try_parse_instruction(substring,VERSION2, &instruction);

        if (!is_parsed) {
            continue;
        }

        if (instruction.type == INST_DO) {
            skip_next_instruction = 0;
            continue;
        }

        if (instruction.type == INST_DONT) {
            skip_next_instruction = 1;
            continue;
        }

        if (skip_next_instruction) {
            continue;
        }

        total += instruction.left_operand * instruction.right_operand;
        i += instruction.end_index - 1;
    }
    return total;
}

//
// Created by romain on 9/12/24.
//

#include <stdio.h>
#include <string.h>

#include "day03_part1.h"
#include "instruction.h"

#define FIRST_VALID_CHAR 'm'

void set_part1_test_data(char *memory_data_array, const int array_size) {
    const char *str = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

    if (strlen(str) > array_size) {
        printf("array size too small \n");
        return;
    }

    strcpy(memory_data_array, str);
}

int get_part1_answer(const char *memory_data_array) {
    int i = 0;
    int total = 0;
    while (i < strlen(memory_data_array)) {
        const char current = memory_data_array[i];

        if (current == FIRST_VALID_CHAR) {
            char substring[MAX_INSTRUCTION_SIZE + 1];
            strncpy(substring, memory_data_array + i, MAX_INSTRUCTION_SIZE);
            substring[MAX_INSTRUCTION_SIZE] = 0;

            Instruction instruction;
            const int is_parsed = try_parse_instruction(substring,VERSION1, &instruction);

            if (is_parsed) {
                // print_instruction(instruction_ptr);
                total += instruction.left_operand * instruction.right_operand;
                i += instruction.end_index - 1;
            }
        }
        i++;
    }
    return total;
}

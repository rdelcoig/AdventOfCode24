//
// Created by romain on 8/12/24.
//

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include "day03.h"

#include "instruction.h"

static void set_test_data(char *memory_data_array, const int array_size) {
    const char str[71] = "xmul(2,4)%&mul[3,7]!@^do_not_mul(5,5)+mul(32,64]then(mul(11,8)mul(8,5))";

    if (strlen(str) > array_size) {
        printf("array size too small \n");
        return;
    }

    strcpy(memory_data_array, str);
}

static void set_answer(const char *memory_data_array, int *answer) {
    int i = 0;
    int total = 0;
    while (i < strlen(memory_data_array)) {
        const char current = memory_data_array[i];

        if (current == FIRST_VALID_CHAR) {
            char substring[MAX_INSTRUCTION_SIZE + 1];
            strncpy(substring, memory_data_array + i, MAX_INSTRUCTION_SIZE);
            substring[MAX_INSTRUCTION_SIZE] = '\0';

            Instruction instruction;
            Instruction *instruction_ptr = &instruction;
            const int is_parsed = try_parse_instruction(substring, instruction_ptr);

            if (is_parsed) {
                const int result = instruction.left_operand * instruction.right_operand;
                printf("%d * %d = %d\n", instruction.left_operand, instruction.right_operand, result);
                total += result;
                i += instruction.end_index - 1;
            }
        }
        i++;
    }
    *answer = total;
}

void set_day03_answer(int *answer) {
    const int memory_data_size = 100;
    char memory_data_array[memory_data_size];
    set_test_data(memory_data_array, memory_data_size);

    set_answer(memory_data_array, answer);
}

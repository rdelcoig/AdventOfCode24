//
// Created by romain on 8/12/24.
//

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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

static void print_instruction(Instruction *instruction) {
    printf(" %s : %d * %d\n",
           instruction->value,
           instruction->left_operand,
           instruction->right_operand);
}

static int read_file_day03(char *raw_data, const int array_size) {
    FILE *file = fopen("../day_03/day03.txt", "r");

    int i = 0;
    char c = 0;
    while ((c = (char) fgetc(file)) != EOF) {
        raw_data[i] = c;
        i++;
        if (i >= array_size) {
            i = -1;
            break;
        }
    }

    fclose(file);
    return i;
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
            memset(instruction.value, 0, MAX_INSTRUCTION_SIZE + 1);
            Instruction *instruction_ptr = &instruction;
            const int is_parsed = try_parse_instruction(substring, instruction_ptr);

            if (is_parsed) {
                // print_instruction(instruction_ptr);
                total += instruction.left_operand * instruction.right_operand;
                i += instruction.end_index - 1;
            }
        }
        i++;
    }
    *answer = total;
}

void set_day03_answer(int *answer) {
    // const int memory_data_size = 100;
    // char memory_data_array[memory_data_size];
    // set_test_data(memory_data_array, memory_data_size);

    const int array_size = 20000;
    char *raw_data = calloc(array_size, sizeof(char));

    read_file_day03(raw_data, array_size);
    set_answer(raw_data, answer); // answer = 175615763

    free(raw_data);
}

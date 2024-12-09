//
// Created by romain on 8/12/24.
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define MAX_INSTRUCTION_SIZE 12
#define FIRST_VALID_CHAR 'm'
#define LAST_VALID_CHAR ')'

typedef struct {
    char value[MAX_INSTRUCTION_SIZE];
    int left_operand;
    int right_operand;
    int end_index;
} Instruction;

int try_parse_instruction(const char *instruction_to_parse, Instruction *instruction);

#endif //INSTRUCTION_H

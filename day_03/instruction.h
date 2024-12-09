//
// Created by romain on 8/12/24.
//

#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#define MAX_INSTRUCTION_SIZE 12
#define INST_MUL 1
#define INST_DONT 2
#define INST_DO 3
#define INST_ERR -1
#define VERSION1 1
#define VERSION2 2

typedef struct {
    char value[MAX_INSTRUCTION_SIZE + 1];
    int end_index;
    int left_operand;
    int right_operand;
    int type;
} Instruction;

int try_parse_instruction(const char *instruction_to_parse, const int version, Instruction *instruction);

#endif //INSTRUCTION_H

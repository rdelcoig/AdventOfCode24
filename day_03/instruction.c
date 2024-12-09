//
// Created by romain on 8/12/24.
//

#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "instruction.h"

struct parse_match {
    int start_index;
    int end_index;
    int left_operand_start_index;
    int left_operand_end_index;
    int right_operand_start_index;
    int right_operand_end_index;
};

static int get_operand(const char *instruction_to_parse, const int start, const int end) {
    const int operand_size = end - start;
    char *operand_str[operand_size + 1];
    memset(operand_str, 0, operand_size + 1);
    strncpy(operand_str, instruction_to_parse + start, operand_size);
    return atoi(operand_str);
}

static int is_valid_instruction(const char *instruction_to_parse,
                                const int version,
                                struct parse_match *parse_match) {
    // fixme : use a non-capturing group for the 1st group of version 2
    const char *pattern = version == VERSION1
                              ? "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)"
                              : "do(n\'t)\?\\(\\)|mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";

    regex_t regex;
    const int status = regcomp(&regex, pattern, REG_EXTENDED);

    if (status != 0) {
        return 0;
    }

    const int match_count = 4; // expression + 2 groups
    regmatch_t matches[match_count];
    const int result = regexec(&regex, instruction_to_parse, match_count, matches, 0);

    // matche[0] = matched expression, matches[1] = left operand, matches[2] = right operand
    if (result == 0) {
        const int full_match_position = 0;
        parse_match->start_index = matches[full_match_position].rm_so;
        parse_match->end_index = matches[full_match_position].rm_eo;

        // it will be filled with -1 when do/don't
        const int left_operand_position = 0 + version;
        parse_match->left_operand_start_index = matches[left_operand_position].rm_so;
        parse_match->left_operand_end_index = matches[left_operand_position].rm_eo;

        const int right_operand_position = 1 + version;
        parse_match->right_operand_start_index = matches[right_operand_position].rm_so;
        parse_match->right_operand_end_index = matches[right_operand_position].rm_eo;
    }

    regfree(&regex);
    return result == 0;
}

int get_instruction_type(const char *instruction_value) {
    if (strstr(instruction_value, "mul(")) {
        return INST_MUL;
    }

    if (strstr(instruction_value, "don't()")) {
        return INST_DONT;
    }

    if (strstr(instruction_value, "do()")) {
        return INST_DO;
    }

    return INST_ERR;
}

void print_instruction(const Instruction *instruction) {
    if (instruction->type == INST_MUL) {
        printf(" %s : %d * %d\n",
               instruction->value,
               instruction->left_operand,
               instruction->right_operand);
    } else {
        printf("%s\n", instruction->value);
    }
}

int try_parse_instruction(const char *instruction_to_parse, const int version, Instruction *instruction) {
    struct parse_match parse_match;

    const int is_valid = is_valid_instruction(instruction_to_parse, version, &parse_match);

    if (is_valid) {
        memset(instruction->value, 0, MAX_INSTRUCTION_SIZE + 1);
        strncpy(instruction->value, instruction_to_parse + parse_match.start_index,
                (parse_match.end_index - parse_match.start_index));
        instruction->end_index = parse_match.end_index;

        const int instruction_type = get_instruction_type(instruction->value);
        instruction->type = instruction_type;

        if (instruction_type == INST_MUL) {
            instruction->left_operand = get_operand(instruction_to_parse, parse_match.left_operand_start_index,
                                                    parse_match.left_operand_end_index);
            instruction->right_operand = get_operand(instruction_to_parse, parse_match.right_operand_start_index,
                                                     parse_match.right_operand_end_index);
        }
    }
    return is_valid;
}

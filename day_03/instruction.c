//
// Created by romain on 8/12/24.
//

#include <regex.h>
#include <stdlib.h>
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

static int is_valid_instruction(const char *instruction_to_parse, struct parse_match *parse_match) {
    const char *regex_pattern = "mul\\(([0-9]{1,3}),([0-9]{1,3})\\)";
    regex_t regex;
    const int status = regcomp(&regex, regex_pattern, REG_EXTENDED);
    if (status != 0) {
        return 0;
    }

    const int match_count = 3; // expression + 2 groups
    regmatch_t matches[match_count];
    const int result = regexec(&regex, instruction_to_parse, match_count, matches, 0);

    // matche[0] = matched expression, matches[1] = left operand, matches[2] = right operand
    if (result == 0) {
        parse_match->start_index = matches[0].rm_so;
        parse_match->end_index = matches[0].rm_eo;
        parse_match->left_operand_start_index = matches[1].rm_so;
        parse_match->left_operand_end_index = matches[1].rm_eo;
        parse_match->right_operand_start_index = matches[2].rm_so;
        parse_match->right_operand_end_index = matches[2].rm_eo;
    }

    regfree(&regex);
    return result == 0;
}

int try_parse_instruction(const char *instruction_to_parse, Instruction *instruction) {
    struct parse_match parse_match;
    const int is_valid = is_valid_instruction(instruction_to_parse, &parse_match);
    if (is_valid) {
        memset(instruction->value, 0, MAX_INSTRUCTION_SIZE);
        strncpy(instruction->value, instruction_to_parse + parse_match.start_index,
                (parse_match.end_index - parse_match.start_index));
        instruction->end_index = parse_match.end_index;
        instruction->left_operand = get_operand(instruction_to_parse, parse_match.left_operand_start_index,
                                                parse_match.left_operand_end_index);
        instruction->right_operand = get_operand(instruction_to_parse, parse_match.right_operand_start_index,
                                                 parse_match.right_operand_end_index);
    }
    return is_valid;
}

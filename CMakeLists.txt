cmake_minimum_required(VERSION 3.25)
project(AdventOfCode24 C)

set(CMAKE_C_STANDARD 23)

add_executable(AdventOfCode24
        main.c
        control.c
        utils.c
        day_01/day01.c
        day_02/day02.c
        day_03/instruction.c
        day_03/day03_part1.c
        day_03/day03_part2.c
        day_03/day03.c
        day_04/day04_utils.c
        day_04/day04_part1.c
        day_04/day04_part2.c
        day_04/day04.c
        day_05/day05_utils.c
        day_05/day05.c
        day_06/day06.c)

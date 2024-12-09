cmake_minimum_required(VERSION 3.30)
project(AdventOfCode24 C)

set(CMAKE_C_STANDARD 23)

add_executable(AdventOfCode24
        main.c
        control.c
        day_01/day01.c
        day_02/day02.c
        day_03/day03.c
        day_03/instruction.c)

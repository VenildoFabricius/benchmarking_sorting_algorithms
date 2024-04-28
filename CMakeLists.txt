cmake_minimum_required(VERSION 3.27)
project(Trabalho C)

set(CMAKE_C_STANDARD 11)

add_executable(Trabalho main.c
        introsort.c
        introsort.h)

MATH(EXPR stack_size "128 * 1024 * 1024") # 128 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

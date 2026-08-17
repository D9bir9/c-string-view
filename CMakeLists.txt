cmake_minimum_required(VERSION 4.3)
project(stringView C)

set(CMAKE_C_STANDARD 11)

add_executable(stringView
        main.c
        string_view.h
        tests.h
)

cmake_minimum_required(VERSION 3.16)
project(student_database C)

set(CMAKE_C_STANDARD 99)

add_executable(student_database main.c database.c database.h)

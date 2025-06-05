cmake_minimum_required(VERSION 3.30)
project(cave)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(grader grader.c cave.cpp)
target_compile_options(grader PRIVATE -fdiagnostics-color=always -fsanitize=undefined -g -O0)
target_link_options(grader PRIVATE -fsanitize=undefined)

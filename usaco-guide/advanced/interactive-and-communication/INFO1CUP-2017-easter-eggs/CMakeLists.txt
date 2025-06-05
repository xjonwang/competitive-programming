cmake_minimum_required(VERSION 3.30)
project(easter)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(grader grader.cpp eggs.cpp)
target_compile_options(grader PRIVATE -fdiagnostics-color=always -fsanitize=undefined -g -O0)
target_link_options(grader PRIVATE -fsanitize=undefined)

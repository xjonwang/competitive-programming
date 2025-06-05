cmake_minimum_required(VERSION 3.30)
project(coins)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(grader grader.cpp coins.cpp)
target_compile_options(grader PRIVATE -fdiagnostics-color=always -fsanitize=undefined -g -O0)
target_link_options(grader PRIVATE -fsanitize=undefined)

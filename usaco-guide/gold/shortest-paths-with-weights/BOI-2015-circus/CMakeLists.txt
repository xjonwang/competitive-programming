cmake_minimum_required(VERSION 3.30)
project(circus)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(grader grader.cpp circus.cpp)

cmake_minimum_required(VERSION 3.10)

project(momoka)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(momoka main.cpp momoka.cpp)

target_include_directories(momoka PRIVATE ${CMAKE_SOURCE_DIR})

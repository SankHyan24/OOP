# ZJU_OOP Assignment 6
# written by: Charles Sun
# date:       2022/05/09
cmake_minimum_required(VERSION 3.15)

project(oop_assignment6)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_executable(oop6)
aux_source_directory(code source)
target_sources(oop6 PUBLIC ${source})
target_include_directories(oop6 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/code)
# ZJU_OOP Assignment 5
# written by: Charles Sun
# date:       2022/04/19
cmake_minimum_required(VERSION 3.15)

project(oop5)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_executable(tmp)
aux_source_directory(code source)
target_sources(tmp PUBLIC ${source})
target_include_directories(tmp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/code)
# ZJU_OOP Assignment Final
# written by: Charles Sun
# date:       2022/05/23
cmake_minimum_required(VERSION 3.15)

project(oop_assignmentx)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3") # 如果是MSVC请将这里设置为/O3

add_subdirectory(lib)
add_subdirectory(code)
add_subdirectory(test)

enable_testing()
add_test(NAME mytest COMMAND Test)
# ZJU_OOP Assignment 4
# written by: Charles Sun
# date:       2022/04/07
cmake_minimum_required(VERSION 3.15)

project(oop4)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

# Base Libraries
add_library(person_diary)
# Personal Diary Library contains the necessary files
aux_source_directory(lib libsource)
target_sources(person_diary PUBLIC ${libsource})
target_include_directories(person_diary PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

# Test Program
# add_executable(test_program code/main.cpp)
# target_include_directories(test_program PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# target_link_libraries(test_program person_diary)

# Person Library Add 
add_executable(pdadd code/pdadd.cpp)
# pdadd is used to add an entity to the diary for the date.
# If an entity of the same date is in the diary, the existing one will be replaced.
# pdadd reads lines of the diary from the stdin, line by line,
# until a line with a single '.' character or the EOF character
# (Ctrl-D in Unix and Ctrl-Z in Windows).
target_link_libraries(pdadd person_diary)

# Person Library List
add_executable(pdlist code/pdlist.cpp)
# pdlist lists all entities in the diary ordered by date.
# If the start and the end date are provided through command line parameters,
# it lists entities between the start and the end only.
# This program lists to the stdout.
target_link_libraries(pdlist person_diary)

# Person Library Show
add_executable(pdshow code/pdshow.cpp)
# pdshow prints the content of the entity specified by the date to the stdout.
target_link_libraries(pdshow person_diary)

# Person Library Remove
add_executable(pdremove code/pdremove.cpp)
# pdremove removes one entity of the date. It returns 0 on success and -1 on failure.
target_link_libraries(pdremove person_diary)




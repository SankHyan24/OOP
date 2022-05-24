# ZJU_OOP Assignment Final
# written by: Charles Sun
# date:       2022/05/23
cmake_minimum_required(VERSION 3.15)

project(oop_assignmentx)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

add_subdirectory(lib)
add_library(tinyxml)
aux_source_directory(lib libsrc)
target_sources(tinyxml PUBLIC ${libsrc})


add_executable(oopx)
aux_source_directory(code source)
target_sources(oopx PUBLIC ${source})
target_include_directories(oopx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/code)
target_include_directories(oopx PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_link_libraries(oopx tinyxml)

enable_testing()
add_subdirectory(test)
add_test(NAME mytest COMMAND Test)
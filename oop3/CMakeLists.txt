cmake_minimum_required(VERSION 3.15)
project(oop3)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
add_executable(oop3)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/map.txt DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
aux_source_directory(code source)
target_sources(oop3 PUBLIC ${source})
target_include_directories(oop3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/code)
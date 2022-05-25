add_library(tinyxml ./tinyxml2.cpp ./tinyxml2.h)
aux_source_directory(./ tinyxmlsrc)
target_sources(tinyxml PUBLIC ${tinyxmlsrc})
target_include_directories(tinyxml PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
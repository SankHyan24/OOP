add_library(tinyxml ./tinyxml2.cpp)
aux_source_directory(lib libsrc)
target_sources(tinyxml PUBLIC ${libsrc})
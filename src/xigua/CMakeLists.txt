set(SOURCE_FILES data.cpp enviroment.cpp error.cpp evaluate.cpp function.cpp parser.cpp stdlib.cpp stdlib/utils.cpp)

include_directories("stdlib")
add_library(xigua ${SOURCE_FILES})

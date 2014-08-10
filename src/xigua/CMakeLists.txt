set(SOURCE_FILES data.cpp data_types.cpp enviroment.cpp error.cpp evaluate.cpp function.cpp parser.cpp stdlib.cpp stdlib/utils.cpp stdlib/benchmark.hpp stdlib/core.hpp stdlib/string.hpp stdlib/types.hpp stdlib/boolean.hpp stdlib/function.hpp stdlib/test.hpp stdlib/containers.hpp stdlib/math.hpp stdlib/tuple.hpp stdlib/utils.hpp ${PROJECT_SOURCE_DIR}/include/xigua/data.hpp ${PROJECT_SOURCE_DIR}/include/xigua/error.hpp ${PROJECT_SOURCE_DIR}/include/xigua/function.hpp ${PROJECT_SOURCE_DIR}/include/xigua/stdlib.hpp ${PROJECT_SOURCE_DIR}/include/xigua/enviroment.hpp ${PROJECT_SOURCE_DIR}/include/xigua/evaluate.hpp ${PROJECT_SOURCE_DIR}/include/xigua/parser.hpp ${PROJECT_SOURCE_DIR}/include/xigua/data_types.hpp ${PROJECT_SOURCE_DIR}/include/xigua/xigua.hpp)


include_directories("stdlib")
add_library(xigua ${SOURCE_FILES})

set(SOURCE_FILES stdlib.cpp utils.cpp record.hpp utils.hpp tuple.hpp benchmark.hpp core.hpp string.hpp types.hpp boolean.hpp function.hpp test.hpp containers.hpp math.hpp ${PROJECT_SOURCE_DIR}/include/xigua/stdlib.hpp)

include_directories("stdlib")
add_library(xigua_stdlib ${SOURCE_FILES})
target_link_libraries(xigua_stdlib xigua_core)
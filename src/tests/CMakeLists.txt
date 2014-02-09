set(SOURCE_FILES main.cpp data.cpp enviroment.cpp evaluate.cpp)

add_executable(unit_tests ${SOURCE_FILES})
target_link_libraries(unit_tests xigua gtest)

add_test(unit_tests ${CMAKE_BINARY_DIR}/unit_tests) 

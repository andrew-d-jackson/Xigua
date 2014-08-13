set(SOURCE_FILES main.cpp)

add_executable(xigua_shell ${SOURCE_FILES})
target_link_libraries (xigua_shell xigua xigua_stdlib)

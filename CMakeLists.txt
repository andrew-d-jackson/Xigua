cmake_minimum_required(VERSION 2.8)

project(xigua)

###############
# Variables
###############

SET(CXX09_FLAGS "${CXX_FLAGS}")
SET(CXX11_FLAGS "${CXX_FLAGS} -std=c++11")

###############
# Settings
###############

SET(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})
SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})

###############
# Options
###############

option(BUILD_SHARED_LIBS "should library be shared or static" OFF)
option(XIGUA_BUILD_SHELL "Build xigua shell" ON)
option(XIGUA_BUILD_TESTS "Build all tests" OFF)

###############
# Xigua Library
###############

include_directories(${PROJECT_SOURCE_DIR}/src ${PROJECT_SOURCE_DIR}/include)
SET(CMAKE_CXX_FLAGS "${CXX11_FLAGS}")
add_subdirectory(${PROJECT_SOURCE_DIR}/src/xigua)

###############
# Xigua Shell
###############

if(XIGUA_BUILD_SHELL)
  add_subdirectory(${PROJECT_SOURCE_DIR}/src/shell)
endif()

###############
# Google Test
###############

if(XIGUA_BUILD_TESTS)
  add_subdirectory(googletest)
  enable_testing()
  include_directories(${gtest_SOURCE_DIR}/include)
endif()

###############
# Unit Tests
###############

if(XIGUA_BUILD_TESTS)
  add_subdirectory(${PROJECT_SOURCE_DIR}/src/tests)
endif()

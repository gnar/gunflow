cmake_minimum_required (VERSION 2.6)
project (gunflow)

find_package(GTest REQUIRED)

set (GUNFLOW_VERSION_MAJOR 0)
set (GUNFLOW_VERSION_MINOR 1)
 
# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
)

file(GLOB MAIN_SOURCES "src/*.cpp" "src/nn/*.cpp")
file(GLOB TEST_SOURCES "test/*.cpp")

set(CMAKE_CXX_FLAGS "-O -Wall")
 
# so that we find config.h
include_directories("${PROJECT_BINARY_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}/src")
 
add_executable(gunflow ${MAIN_SOURCES} main.cpp)

# Unit Tests
add_executable(gunflow-tests ${MAIN_SOURCES} ${TEST_SOURCES} test.cpp)
include_directories(${GTEST_INCLUDE_DIRS})
target_link_libraries(gunflow-tests gtest gtest_main)


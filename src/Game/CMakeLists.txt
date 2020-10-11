cmake_minimum_required(VERSION 3.17)

project(Game)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(LIBRARY_BUILD_DIR build)

# Get sources
file(GLOB_RECURSE SRC
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.cpp"
        )

add_executable(Game ${SRC})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Serum engine
target_link_libraries(Game PRIVATE serum)
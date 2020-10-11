cmake_minimum_required(VERSION 3.17)

project(Editor)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(RESOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/resources)
set(LIBRARY_BUILD_DIR build)

# Get sources
file(GLOB_RECURSE SRC
        "${SOURCE_DIR}/*.h"
        "${SOURCE_DIR}/*.cpp"
        )

add_executable(Editor ${SRC})

# Resources
file(GLOB_RECURSE RESOURCES ${RESOURCE_DIR}/*)

cmrc_add_resource_library(resources NAMESPACE res WHENCE ${RESOURCE_DIR} ${RESOURCES})

# Set output
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Precompiled header
target_precompile_headers(Editor PRIVATE ${SOURCE_DIR}/pch.h)

# Serum engine
target_link_libraries(Editor PRIVATE serum)
target_link_libraries(Editor PRIVATE resources)
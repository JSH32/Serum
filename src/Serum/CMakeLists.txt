cmake_minimum_required(VERSION 3.17)

set(VERSION 0.0.1)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

project(Serum VERSION ${VERSION} DESCRIPTION "The serum 2d game engine")
set(CMAKE_CXX_STANDARD 17)

# Get files
file(GLOB_RECURSE SRC ${SOURCE_DIR}/*.cpp)

add_library(serum SHARED ${SRC})
target_include_directories(serum PUBLIC ${SOURCE_DIR})
target_include_directories(serum PUBLIC ${INCLUDE_DIR})

target_precompile_headers(serum PUBLIC ${SOURCE_DIR}/Serum/pch.h)

# -- SET VARIABLES --

# Getting github branch
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Get the latest abbreviated commit hash of the working branch
execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

# Set variables
add_definitions("-DGIT_COMMIT_HASH=${GIT_COMMIT_HASH}")
add_definitions("-DGIT_BRANCH=${GIT_BRANCH}")

# -- INITIALIZE LIBRARIES --

# glfw : window library
target_link_libraries(serum PUBLIC glfw)
target_include_directories(serum PUBLIC ${VENDOR_DIR}/glfw/include/GLFW)
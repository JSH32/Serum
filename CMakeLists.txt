cmake_minimum_required(VERSION 3.17)
project(SerumProject)

# Include CMake scripts
set(SCRIPT_DIR ${CMAKE_CURRENT_LIST_DIR}/extra/cmake)
include(${SCRIPT_DIR}/CMakeRC.cmake)

# Dependency directory
set(VENDOR_DIR ${CMAKE_CURRENT_LIST_DIR}/vendor)
set(LIBRARY_BUILD_DIR build)

# Dependency build targets
# glfw : window lib
add_subdirectory(${VENDOR_DIR}/glfw ${LIBRARY_BUILD_DIR}/glfw)

# bgfx : graphics API
set(BX_DIR ${VENDOR_DIR}/bx)
set(BIMG_DIR ${VENDOR_DIR}/bimg)
set(BGFX_DIR ${VENDOR_DIR}/bgfx)

include(extra/cmake/bgfx/shared.cmake)
include(extra/cmake/bgfx/bx.cmake)
include(extra/cmake/bgfx/bimg.cmake)
include(extra/cmake/bgfx/bgfx.cmake)

# Build targets for this serum
add_subdirectory(src/Serum)
add_subdirectory(src/Game)
add_subdirectory(src/Editor)
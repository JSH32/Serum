cmake_minimum_required(VERSION 3.17)
project(SerumProject)

# Include CMake scripts
set(SCRIPT_DIR ${CMAKE_CURRENT_LIST_DIR}/extra/cmake)
include(${SCRIPT_DIR}/CMakeRC.cmake)

# Dependency directory
set(VENDOR_DIR ${CMAKE_CURRENT_LIST_DIR}/vendor)
set(LIBRARY_BUILD_DIR build)

# Dependency build targets
# glfw
add_subdirectory(${VENDOR_DIR}/glfw ${LIBRARY_BUILD_DIR}/glfw)

# glad
add_subdirectory(${VENDOR_DIR}/glad)

# imgui
file(GLOB IMGUI_SRC ${VENDOR_DIR}/imgui/*.cpp ${VENDOR_DIR}/imgui_impl/*.cpp)
add_library(imgui ${IMGUI_SRC})
target_include_directories(imgui PUBLIC ${VENDOR_DIR}/imgui ${VENDOR_DIR}/imgui_impl)
target_link_libraries(imgui PRIVATE glad)

# glm
add_subdirectory(${VENDOR_DIR}/glm)

# Build targets for this serum
add_subdirectory(src/Serum)
add_subdirectory(src/Game)
add_subdirectory(src/Editor)
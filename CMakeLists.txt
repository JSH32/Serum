cmake_minimum_required(VERSION 3.21)
project(Serum2d)

set(CMAKE_CXX_STANDARD 17)

# Dependency directory
set(VENDOR_DIR ${CMAKE_CURRENT_LIST_DIR}/vendor)
set(LIBRARY_BUILD_DIR build)

# sfml
add_subdirectory(${VENDOR_DIR}/SFML)
add_subdirectory(${VENDOR_DIR}/Thor)

# entt
add_subdirectory(${VENDOR_DIR}/entt)

# spdlog
add_subdirectory(${VENDOR_DIR}/spdlog)

# box2d
add_subdirectory(${VENDOR_DIR}/box2d)

# imgui
set(IMGUI_SFML_FIND_SFML OFF) # sfml already imported, no need to use find_package
set(IMGUI_DIR ${VENDOR_DIR}/imgui)
add_subdirectory(${VENDOR_DIR}/imgui-sfml)

# subprojects
add_subdirectory(src/core)
add_subdirectory(src/editor)
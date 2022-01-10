cmake_minimum_required(VERSION 3.21)
project(Serum2d)

set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(_HAS_AUTO_PTR_ETC=1) # Enable auto_ptr in MSVC

# Link settings for external libraries
set(BUILD_SHARED_LIBS FALSE)
set(THOR_STATIC_STD_LIBS TRUE)
set(THOR_SHARED_LIBS FALSE)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

set_target_properties(
	aob
	box2d
	glad
	glfw
	imgui
	ImGui-SFML
	Resources
	sajson
	spdlog
	testbed
	unit_test
	PROPERTIES FOLDER Libraries
)

set_target_properties(
	editor
	serum
	PROPERTIES FOLDER Serum
)

set_target_properties(PROPERTIES FOLDER SFML)
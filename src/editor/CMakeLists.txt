project(SerumEditor)

set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

# Get sources
file(GLOB_RECURSE SRC
        "${SOURCE_DIR}/*.cpp"
        "${SOURCE_DIR}/*.c"
        "${SOURCE_DIR}/*.h"
        )

add_executable(editor ${SRC} src/imgui_utils.cpp)

target_link_libraries(editor PRIVATE serum)
target_include_directories(editor PRIVATE ${SOURCE_DIR})

# CmakeRC
include(${VENDOR_DIR}/cmrc/CMakeRC.cmake)

set(RESOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/resources)
file(GLOB_RECURSE RESOURCES ${RESOURCE_DIR}/*)
cmrc_add_resource_library(resources NAMESPACE resources WHENCE ${RESOURCE_DIR} ${RESOURCES})
target_link_libraries(editor PRIVATE resources)

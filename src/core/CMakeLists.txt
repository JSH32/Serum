project(SerumCore)

# Variables
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

file(GLOB_RECURSE SRC
        ${SOURCE_DIR}/*.cpp
        ${SOURCE_DIR}/*.c
        ${SOURCE_DIR}/*.h)

add_library(serum STATIC ${SRC} src/Serum/math_utils.cpp src/Serum/math_utils.h)
target_include_directories(serum PUBLIC ${SOURCE_DIR})
target_include_directories(serum PUBLIC ${INCLUDE_DIR})
target_include_directories(serum PUBLIC ${VENDOR_DIR}/entt/single_include/entt)

target_link_libraries(serum PUBLIC sfml-graphics sfml-window sfml-system)
target_link_libraries(serum PUBLIC EnTT::EnTT)
target_link_libraries(serum PUBLIC ImGui-SFML::ImGui-SFML)
target_link_libraries(serum PUBLIC spdlog)
target_link_libraries(serum PUBLIC thor)

target_include_directories(serum PUBLIC ${VENDOR_DIR}/Thor/include ${VENDOR_DIR}/Thor/extlibs/aurora/include)

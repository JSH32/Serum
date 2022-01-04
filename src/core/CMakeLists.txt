project(SerumCore)

# Variables
set(SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_LIST_DIR}/include)

file(GLOB_RECURSE SRC
        ${SOURCE_DIR}/*.cpp
        ${SOURCE_DIR}/*.c)

add_library(serum ${SRC} src/entity.cpp src/entity.h src/scene.cpp src/scene.h)
target_include_directories(serum PUBLIC ${SOURCE_DIR})
target_include_directories(serum PUBLIC ${INCLUDE_DIR})
target_include_directories(serum PUBLIC ${VENDOR_DIR}/entt/single_include/entt)

target_link_libraries(serum PUBLIC sfml-graphics sfml-audio)
target_link_libraries(serum PUBLIC EnTT::EnTT)
target_link_libraries(serum PUBLIC ImGui-SFML::ImGui-SFML)
cmake_minimum_required(VERSION 3.13)

project(sokoban)

set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

link_libraries(GLEW::GLEW OpenGL::GL SDL2::Main SDL2::Image)

include_directories(${PROJECT_SOURCE_DIR}/vendor/glm)
include_directories(${PROJECT_SOURCE_DIR}/vendor/entt/single_include)

file(GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_executable(sokoban ${SOURCE_FILES} ${HEADER_FILES})

# copy over the settings file for the game
add_custom_command(
    TARGET sokoban PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_SOURCE_DIR}/settings.ini
                ${CMAKE_CURRENT_BINARY_DIR}/settings.ini)

add_custom_command(
    TARGET sokoban PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_SOURCE_DIR}/assets
                ${CMAKE_CURRENT_BINARY_DIR}/assets)

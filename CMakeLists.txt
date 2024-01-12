cmake_minimum_required(VERSION 3.13)

project(sokoban)
set(CMAKE_CXX_STANDARD 20)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

link_libraries(GLEW::GLEW OpenGL::GL)
link_libraries(SDL2::Main SDL2::Image)

include_directories(vendor/glm)

set(HEADER_FILES src/settings.h src/display.h src/audio.h src/assets.h src/level.h src/camera.h)
set(SOURCE_FILES src/sokoban.cpp src/settings.cpp src/display.cpp src/audio.cpp src/assets.cpp src/level.cpp src/camera.cpp)

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

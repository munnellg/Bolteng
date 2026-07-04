cmake_minimum_required(VERSION 3.13)

project(bolteng VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(JSON_BuildTests OFF CACHE INTERNAL "")

include(FetchContent)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

add_library(bolteng ${SOURCE_FILES} )

target_include_directories(bolteng PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_include_directories(bolteng PRIVATE ${ASSIMP_INCLUDE_DIRS})
target_include_directories(bolteng PRIVATE ${PROJECT_SOURCE_DIR}/vendor/glm)
target_include_directories(bolteng PRIVATE ${PROJECT_SOURCE_DIR}/vendor/entt/single_include)

target_link_libraries(bolteng GLEW::GLEW OpenGL::GL SDL2::Main SDL2::Image)
target_link_libraries(bolteng ${ASSIMP_LIBRARIES})

target_compile_options(bolteng PRIVATE -Wall -Wextra -Wpedantic)

add_subdirectory(examples)
add_subdirectory(tests)
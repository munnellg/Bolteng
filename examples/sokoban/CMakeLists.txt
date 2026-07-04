file(GLOB_RECURSE HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")

add_executable(sokoban ${SOURCE_FILES} ${HEADER_FILES})
target_link_libraries(sokoban PRIVATE bolteng)
target_include_directories(sokoban PRIVATE ${PROJECT_SOURCE_DIR}/vendor/entt/single_include)

target_compile_options(sokoban PRIVATE -Wall -Wextra -Wpedantic)

#copy over the settings file for the game
add_custom_command(
    TARGET sokoban PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                ${CMAKE_CURRENT_SOURCE_DIR}/settings.ini
                ${CMAKE_CURRENT_BINARY_DIR}/settings.ini)

add_custom_command(
    TARGET sokoban PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
                ${CMAKE_CURRENT_SOURCE_DIR}/assets
                ${CMAKE_CURRENT_BINARY_DIR}/assets)

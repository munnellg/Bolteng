FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1 # or a later release
)

FetchContent_MakeAvailable(Catch2)

file(GLOB_RECURSE TEST_SOURCE_FILES "${PROJECT_SOURCE_DIR}/tests/*.cpp")

add_executable(testbolteng ${TEST_SOURCE_FILES})

target_link_libraries(testbolteng PRIVATE bolteng Catch2::Catch2WithMain)

add_test(NAME testbolteng COMMAND testbolteng)
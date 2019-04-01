cmake_minimum_required(VERSION 3.11)
project(simple-voxels VERSION 0.0.0 LANGUAGES CXX)

add_subdirectory(src/engine)
add_subdirectory(src/game)

option(BUILD_TESTS OFF)
if (BUILD_TESTS)
    enable_testing()

    add_subdirectory(external/catch2)
    # A somewhat hacky way to add the Catch2 cmake modules to the project...
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/external/catch2/contrib")

    add_subdirectory(tests)
endif()

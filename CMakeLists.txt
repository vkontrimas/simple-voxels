################################################################################
# Config                                                                       #
################################################################################
cmake_minimum_required(VERSION 3.11)
project(simple-voxels VERSION 0.0.0 LANGUAGES C CXX)

# Directory to which the game files are copied.
set(SIVOX_GAME_OUTPUT ${CMAKE_BINARY_DIR}/game)

################################################################################
# External libraries                                                           #
################################################################################
add_subdirectory(external/sdl2)
add_subdirectory(external/glm)
add_subdirectory(external/glad)

################################################################################
# Source code                                                                  #
################################################################################
add_subdirectory(src)

################################################################################
# Unit testing                                                                 #
################################################################################
option(SIVOX_BUILD_TESTS OFF)
if (SIVOX_BUILD_TESTS)
    enable_testing()

    add_subdirectory(external/catch2)
    # A somewhat hacky way to add the Catch2 cmake modules to the project...
    list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/external/catch2/contrib")

    add_subdirectory(tests)
endif()

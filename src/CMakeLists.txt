set(
    GAME_SOURCE
    common.hpp
    gamestate.hpp
    input.hpp
    input.cpp
    voxelterrain.hpp
    voxelterrain.cpp
    meshgenerator.hpp
    meshgenerator.cpp
    ioutils.hpp
    ioutils.cpp
    shader.hpp
    shader.cpp
    chunkbuffers.hpp
    chunkbuffers.cpp
)

set(GAME_LIBRARIES SDL2 glm glad)
set(GAME_FEATURES cxx_std_17)

add_executable(game WIN32 main.cpp ${GAME_SOURCE})
target_link_libraries(game PRIVATE SDL2main ${GAME_LIBRARIES})
target_compile_features(game PRIVATE ${GAME_FEATURES})

add_custom_command(
    TARGET game
    POST_BUILD

    # Copy the game executable and the SDL dyn lib to the build/game folder. 
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:game> ${SIVOX_GAME_OUTPUT}/$<TARGET_FILE_NAME:game>
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL2> ${SIVOX_GAME_OUTPUT}/$<TARGET_FILE_NAME:SDL2>

    # Copy the SDL dyn lib to the actual path where the original game executable ends up.
    # (So we can run it when debugging!)
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL2> $<TARGET_FILE_DIR:game>/$<TARGET_FILE_NAME:SDL2>
)

# Creating a static library for testing
add_library(gametestlib STATIC ${GAME_SOURCE})
target_compile_definitions(gametestlib PUBLIC SIVOX_TESTING)
target_include_directories(gametestlib PUBLIC .)
target_link_libraries(gametestlib PUBLIC ${GAME_LIBRARIES})
target_compile_features(gametestlib PRIVATE ${GAME_FEATURES})

# Linux support.
# Older clang and gcc require linking against some libs for <filesytem> support
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang" OR "${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU") 
    target_link_libraries(game PRIVATE stdc++fs)
    target_link_libraries(gametestlib PRIVATE stdc++fs)
endif()

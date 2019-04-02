set(
    GAME_SOURCE
    main.cpp
)

add_executable(game WIN32 ${GAME_SOURCE})
target_link_libraries(game PRIVATE engine SDL2 SDL2main glm glad)
target_compile_features(game PRIVATE cxx_std_11)

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

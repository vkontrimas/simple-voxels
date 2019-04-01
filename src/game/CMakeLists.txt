set(
    GAME_SOURCE
    main.cpp
)

add_executable(game ${GAME_SOURCE})
target_link_libraries(game PRIVATE engine SDL2)
target_compile_features(game PRIVATE cxx_std_11)

include(CTest)
include(Catch)

set(
    TEST_SOURCES
    main.cpp
    input.cpp
    voxelterrain.cpp
)
add_executable(testgame ${TEST_SOURCES})
# target_include_directories(testgame PRIVATE $<TARGET_PROPERTY:game,SOURCE_DIR>)
# TODO: Get rid of SDL2 linkage
target_link_libraries(testgame PRIVATE Catch2::Catch2 gametestlib)
target_compile_features(testgame PRIVATE cxx_std_11)

add_custom_command(
    TARGET testgame
    POST_BUILD

    # We need the SDL dyn lib for some stuff
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:SDL2> $<TARGET_FILE_DIR:testgame>/$<TARGET_FILE_NAME:SDL2>
)

catch_discover_tests(testgame)

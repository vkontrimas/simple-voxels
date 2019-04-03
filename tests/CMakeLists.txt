include(CTest)
include(Catch)

set(
    TEST_SOURCES
    main.cpp
)
add_executable(testgame ${TEST_SOURCES})
target_include_directories(testgame PRIVATE $<TARGET_PROPERTY:game,SOURCE_DIR>)
target_compile_features(testgame PRIVATE cxx_std_11)
target_link_libraries(testgame PRIVATE Catch2::Catch2)

catch_discover_tests(testgame)

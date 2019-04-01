include(CTest)
include(Catch)

set(
    TEST_SOURCES
    main.cpp
)
add_executable(testengine ${TEST_SOURCES})
target_compile_features(testengine PRIVATE cxx_std_11)
target_link_libraries(testengine PRIVATE Catch2::Catch2 engine)

catch_discover_tests(testengine)

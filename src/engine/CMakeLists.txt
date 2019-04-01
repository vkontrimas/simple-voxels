set(
    ENGINE_SOURCE
    placeholder.cpp
)

add_library(engine STATIC ${ENGINE_SOURCE})
target_compile_features(engine PRIVATE cxx_std_11)

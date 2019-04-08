set(
    DATA_FILES
    shaders/test.vert
    shaders/test.frag
)

add_custom_target(
    data ALL
    DEPENDS ${DATA_FILES}
)

foreach(file ${DATA_FILES})
    add_custom_command(
        OUTPUT ${file}
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/${file} ${CMAKE_CURRENT_BINARY_DIR}/${file}
        COMMENT Copying ${file}
    )
endforeach()

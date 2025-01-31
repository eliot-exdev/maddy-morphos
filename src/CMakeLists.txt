cmake_minimum_required(VERSION 3.25)

# some helper
function(strip_target TARGET_NAME)
    if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
        if (APPLE)
            add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                    COMMAND ${CMAKE_STRIP} $<TARGET_FILE:${TARGET_NAME}>
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "stripping target ${TARGET_NAME}"
            )
        else ()
            add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
                    COMMAND ${CMAKE_STRIP} --strip-debug --strip-unneeded $<TARGET_FILE:${TARGET_NAME}>
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "stripping target ${TARGET_NAME}"
            )
        endif ()
    endif ()
endfunction()

add_executable(md2html
    main.cpp
)
target_link_libraries(md2html
    PRIVATE maddy
)
strip_target(md2html)

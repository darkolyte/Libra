# Create executables for our project

# Build release version
if (CMAKE_BUILD_TYPE STREQUAL "Release")

    # Build type message
    message(STATUS "Building release version")
    
    # Executable for windows systems
    if (WIN32)
        add_executable(${PROJECT_NAME} WIN32)
    endif(WIN32)

    # Executable for apple systems
    if (APPLE)
        add_executable(${PROJECT_NAME} MACOSX_BUNDLE)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_CURRENT_LIST_DIR}/assets"
            "$<TARGET_FILE_DIR:${PROJECT_NAME}>/../Resources/assets"
        )
    endif(APPLE)

    # Executable for linux systems
    if (UNIX AND NOT APPLE)
        add_executable(${PROJECT_NAME})
    endif(UNIX AND NOT APPLE)

endif (CMAKE_BUILD_TYPE STREQUAL "Release")

# Build debug version
if (CMAKE_BUILD_TYPE STREQUAL "Debug")

    # Build type message
    message(STATUS "Building debug version")

    # Add executable
    add_executable(${PROJECT_NAME})

endif (CMAKE_BUILD_TYPE STREQUAL "Debug")

# Copies assets to build directory
add_custom_target(COPY_ASSETS
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_LIST_DIR}/copy-assets.cmake
)

# Make sure that assets are copied before building our project
add_dependencies(${PROJECT_NAME} COPY_ASSETS)

# Include directories for our executable
target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
        inc/libra.h
)

# Source files for our executable
target_sources(
    ${PROJECT_NAME}
    PRIVATE
        main.cpp
        libra.cpp
)

# Libraries to link to our executable
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        lib
)
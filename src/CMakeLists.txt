# Create executable for our project
add_executable(${PROJECT_NAME})

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
)

# Libraries to link to our executable
target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
        lib
)
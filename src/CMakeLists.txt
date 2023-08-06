# Create executable for our project
add_executable(${PROJECT_NAME})

# Source files for our executable
target_sources(${PROJECT_NAME}
    PRIVATE
        main.cpp
)

# Libraries to link to our executable
target_link_libraries(${PROJECT_NAME}
    PRIVATE
        lib
)
# Do not build SDL tests 
set(SLD_TEST OFF CACHE BOOL "" FORCE)

# Add SDL directory
add_subdirectory(SDL)

# Interface library so our project links to everything SDL3 does
add_library(lib INTERFACE)
target_link_libraries(
    lib 
    INTERFACE 
    SDL3::SDL3
)
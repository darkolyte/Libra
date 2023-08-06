# Set Minimum CMake Version
cmake_minimum_required (VERSION 3.16)

# Set C++ Standard, do not use GNU extensions
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Setup Project
project(Libra)

# Set C++ Flags - append to existing flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

# Add Source Directory
set(SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)

# Add Source Files
file(GLOB_RECURSE SOURCE_FILES ${SOURCE_DIR}/*.cpp)

# Add Executable
add_executable(Libra ${SOURCE_FILES}) 

# Adding SDL2 Include Directory
target_include_directories(
    Libra 
    PRIVATE
    /opt/homebrew/include/SDL2
)

# Link SDL2 Library
target_link_libraries(
    Libra
    PRIVATE
    /opt/homebrew/Cellar/sdl2/2.28.1/lib/libSDL2.dylib
)
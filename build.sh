#!/bin/sh

# Allow build type to be specified as an argument
if [ $# -gt 1 ]; then
    echo "Usage: ./build.sh [build_type]"
    exit 1
elif [ $# -eq 1 ]; then
    if [ $1 = "-d" ]; then
        BUILD_TYPE=Debug
    elif [ $1 = "-r" ]; then
        BUILD_TYPE=Release
    else
        echo "Usage: ./build.sh -> Defaults to Release\n./build.sh -d -> Debug\n./build.sh -r -> Release"
        exit 1
    fi
else
    BUILD_TYPE=Release
fi

# Generate build files for Ninja
cmake -B build -G Ninja -DBUILD_SHARED_LIBS=ON -DCMAKE_BUILD_TYPE=$BUILD_TYPE

# Build the project
cd build && ninja
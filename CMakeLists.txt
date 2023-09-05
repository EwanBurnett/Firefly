cmake_minimum_required(VERSION 3.12)

project("Firefly" VERSION 0.1)

# Download any dependencies

# Check language support

# Build the project
add_executable("Firefly" src/main.cpp)
target_compile_definitions("Firefly" PUBLIC FIREFLY_VERSION_MAJOR=${Firefly_VERSION_MAJOR} FIREFLY_VERSION_MINOR=${Firefly_VERSION_MINOR})

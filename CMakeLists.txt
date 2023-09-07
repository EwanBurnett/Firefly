cmake_minimum_required(VERSION 3.12)

project("Firefly" VERSION 0.1)

# Download any dependencies
find_package(Threads REQUIRED)
include(FetchContent)

# STB
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
)

# TinyXML2
FetchContent_Declare(
    tinyxml2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2.git
)

FetchContent_MakeAvailable(stb tinyxml2)


# Build the project
add_executable("Firefly" src/main.cpp src/RayTracer.cpp src/World.cpp ${tinyxml2_SOURCE_DIR}/tinyxml2.cpp)
target_include_directories("Firefly" PRIVATE  ${stb_SOURCE_DIR} ${tinyxml2_SOURCE_DIR})
target_link_libraries("Firefly" Threads::Threads)
target_compile_definitions("Firefly" PUBLIC FIREFLY_VERSION_MAJOR=${Firefly_VERSION_MAJOR} FIREFLY_VERSION_MINOR=${Firefly_VERSION_MINOR})

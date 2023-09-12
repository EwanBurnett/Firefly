cmake_minimum_required(VERSION 3.12)

project("Firefly" VERSION 0.3)

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
    TinyXML2
    GIT_REPOSITORY https://github.com/leethomason/tinyxml2
)

FetchContent_MakeAvailable(stb tinyxml2)


# Build the project
add_executable("Firefly" src/main.cpp src/World.cpp src/ColourRGBA.cpp)
target_include_directories("Firefly" PRIVATE  ${stb_SOURCE_DIR} ${tinyxml2_SOURCE_DIR})
target_link_libraries("Firefly" Threads::Threads tinyxml2::tinyxml2)
target_compile_definitions("Firefly" PUBLIC FIREFLY_VERSION_MAJOR=${Firefly_VERSION_MAJOR} FIREFLY_VERSION_MINOR=${Firefly_VERSION_MINOR})

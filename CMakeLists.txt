cmake_minimum_required(VERSION 3.12)

project("Firefly" VERSION 0.1)

find_package(Threads REQUIRED)
find_package(Vulkan REQUIRED)

# Download any dependencies
include(FetchContent)

# STB
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.9
)

FetchContent_MakeAvailable(stb glfw)


# Build the project
add_executable("Firefly" src/main.cpp "include/Viewer/Viewer.h" "include/Viewer/Window.h" "src/Viewer/Viewer.cpp" "src/Viewer/Window.cpp" "include/Viewer/Engine.h" "src/Viewer/Engine.cpp" "include/Viewer/VkHelpers.h" "src/Viewer/VkHelpers.cpp")
target_include_directories("Firefly" PRIVATE  ${stb_SOURCE_DIR})
target_link_libraries("Firefly" Threads::Threads Vulkan::Vulkan glfw)
target_compile_definitions("Firefly" PUBLIC FIREFLY_VERSION_MAJOR=${Firefly_VERSION_MAJOR} FIREFLY_VERSION_MINOR=${Firefly_VERSION_MINOR})

# Force utf-8 for MSVC
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

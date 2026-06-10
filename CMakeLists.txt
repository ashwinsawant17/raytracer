cmake_minimum_required(VERSION 3.20)
project(Raytracer LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Separate output directories per config
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)

include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.18
)

FetchContent_MakeAvailable(SDL3)

add_executable(raytracer
    src/main.cpp
    src/image.cpp
    src/primitive.cpp
    src/texture.cpp
    src/raytracer.cpp
    src/light.cpp
)

target_include_directories(raytracer PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(raytracer PRIVATE SDL3::SDL3)

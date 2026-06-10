cmake_minimum_required(VERSION 3.20)
project(Raytracer LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Separate output directories per config
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/Debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/Release)

if(WIN32)
    include(FetchContent)

    FetchContent_Declare(
        SDL3
        GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
        GIT_TAG release-3.2.18
    )

    FetchContent_MakeAvailable(SDL3)
endif()

add_executable(raytracer
    src/main.cpp
    src/image.cpp
    src/primitive.cpp
    src/texture.cpp
    src/raytracer.cpp
    src/light.cpp
)

if(UNIX)
    option(ENABLE_PROFILING "Enable gprof profiling" OFF)

    if(ENABLE_PROFILING)
        target_compile_options(raytracer PRIVATE -pg)
        target_link_options(raytracer PRIVATE -pg)
    endif()
endif()

target_include_directories(raytracer PUBLIC 
    ${CMAKE_SOURCE_DIR}/include
)

if(WIN32)
    target_link_libraries(raytracer PRIVATE SDL3::SDL3)
endif()

cmake_minimum_required(VERSION 3.20)
project(Raycaster)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(FetchContent)

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.2.18 # or whatever stable release you choose
)

FetchContent_MakeAvailable(SDL3)

add_executable(raycaster
    ${PROJECT_SOURCE_DIR}/src/main.cpp
)

target_include_directories(raycaster PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(raycaster PRIVATE SDL3::SDL3)
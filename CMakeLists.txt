cmake_minimum_required(VERSION 3.14)

project(superflame)

message(STATUS "CMAKE_SOURCE_DIR: ${CMAKE_SOURCE_DIR}")

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

add_subdirectory(test)
add_subdirectory(example)

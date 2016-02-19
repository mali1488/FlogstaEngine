cmake_minimum_required(VERSION 2.6)
project(FLOGSTA_ENGINE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(OUTPUT ${PROJECT_SOURCE_DIR})

find_package(SDL2 REQUIRED)


# Set env
set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

# Add sub-folders/projects
add_subdirectory(src)

# Printing
message("binary tree path: ${PROJECT_BINARY_DIR}")
message("CXX FLAGS: ${CMAKE_CXX_FLAGS}")
message("${PROJECT_SOURCE_DIR}/build = ${PROJECT_SOURCE_DIR}/build")

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR} )
# Adding target executable


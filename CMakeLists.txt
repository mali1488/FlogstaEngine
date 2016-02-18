cmake_minimum_required(VERSION 2.6)
project(FLOGSTA_ENGINE)


# Set env
set(CMAKE_CXX_FLAGS "-g -Wall")

# Add sub-folders/projects
add_subdirectory(src)

# Printing
message("binary tree path: ${PROJECT_BINARY_DIR}")
message("CXX FLAGS: ${CMAKE_CXX_FLAGS}")

# Adding target executable


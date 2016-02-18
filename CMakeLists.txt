cmake_minimum_required(VERSION 2.6)
project(FLOGSTA_ENGINE)

find_package(OpenGL)

set(CMAKE_CXX_FLAGS "-g -Wall")
add_subdirectory(src)

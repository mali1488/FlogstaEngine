cmake_minimum_required(VERSION 2.6)
project(FLOGSTA_ENGINE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(OUTPUT ${PROJECT_SOURCE_DIR})



# Set env
set(CMAKE_CXX_FLAGS "-g -ggdb -Wall -std=c++11")

# Add OS Specific cpp flags
if (WIN32)
  message("Windows 32 bit detected")
elseif (UNIX AND NOT APPLE)
  set(LINUX TRUE)
elseif (APPLE)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -framework OpenGL -lglew")
endif(WIN32)
if(LINUX)
  message("Linux OS detected")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif(LINUX)

# Add sub-folders/projects
add_subdirectory(src)

# Printing
message("CXX FLAGS: ${CMAKE_CXX_FLAGS}")
message("${PROJECT_SOURCE_DIR}/build = ${PROJECT_SOURCE_DIR}/build")

#set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR} )
# Adding target executable


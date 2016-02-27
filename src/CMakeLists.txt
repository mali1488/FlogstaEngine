project(FLOGSTA_ENGINE_SRC)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(SDL2 REQUIRED)

set(FE_SOURCES FlogstaEngine.cpp ShaderLibrary.cpp FeEventHandler.cpp OBJFileReader.cpp ShaderProgram.cpp Mesh3D.cpp Mesh2D.cpp main.cpp)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../build )

add_executable(FE ${FE_SOURCES})


if (OPENGL_FOUND)
    include_directories(${OPENGL_INCLUDE_DIRS})
    target_link_libraries(FE ${OPENGL_LIBRARIES})
    message("OpenGL include dir: ${OPENGL_INCLUDE_DIR}")
    message("OpenGL lib dir: ${OPENGL_LIBRARIES}")    
endif()

if (GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIRS})
    target_link_libraries(FE ${GLEW_LIBRARIES})
    message("GLEW include dir: ${GLEW_INCLUDE_DIR}")
    message("GLEW lib dir: ${GLEW_LIBRARIES}")
endif()

if (SDL2_FOUND)
  include_directories(${SDL2_INCLUDE_DIR})
  target_link_libraries(FE ${SDL2_LIBRARY})
  message("SDL2 include dir: ${SDL2_INCLUDE_DIR}")
  message("SDL2 lib dir: ${SDL2_LIBRARY}")    
endif()

# ${SDL2_IMAGE_INCLUDE_DIR}
# ${SDL2_TTF_INCLUDE_DIR})

get_property(include_dirs_fe DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
get_property(library_dirs_fe DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INTERFACE_LINK_LIBRARIES)

message("Final flag string:")
message("${CMAKE_CXX_FLAGS}")
message("Final include string:")
message("${include_dirs_fe}")
message("Final lib string:")
message("${library_dirs_fe}")




# ${SDL2_IMAGE_LIBRARIES}
# ${SDL2_TTF_LIBRARIES})
#install(TARGETS FE DESTINATION ${OUTPUT}/build)

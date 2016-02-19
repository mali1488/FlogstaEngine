project(FLOGSTA_ENGINE_SRC)

find_package(OpenGL REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
#                    ${SDL2_IMAGE_INCLUDE_DIR}
#                    ${SDL2_TTF_INCLUDE_DIR})

message("SDL2 include dir: ${SDL2_INCLUDE_DIR}")

set(FE_SOURCES FlogstaEngine.cpp FeEventHandler.cpp OBJFileReader.cpp)
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../build )

add_executable(FE ${FE_SOURCES})


target_link_libraries(FE ${SDL2_LIBRARY})
#                             ${SDL2_IMAGE_LIBRARIES}
#                             ${SDL2_TTF_LIBRARIES})
#install(TARGETS FE DESTINATION ${OUTPUT}/build)

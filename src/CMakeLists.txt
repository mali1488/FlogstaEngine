project(FLOGSTA_ENGINE_SRC)

find_package(OpenGL)
find_package(SDL2)


include_directories(${SDL2_INCLUDE_DIR})
#                    ${SDL2_IMAGE_INCLUDE_DIR}
#                    ${SDL2_TTF_INCLUDE_DIR})
target_link_libraries(target ${SDL2_LIBRARY})
#                             ${SDL2_IMAGE_LIBRARIES}
#                             ${SDL2_TTF_LIBRARIES})


add_executable(FE FlogstaEngine.cpp)

#include "LibIncludes.hpp"
#include "FeEventHandler.hpp"
#include "OBJFileReader.hpp"
#include "ShaderProgram.hpp"
#include "FlogstaEngine.hpp"
#include "Mesh3D.hpp"
#include "Mesh2D.hpp"
// Deps
#include "../deps/glm/glm/glm.hpp"
#include "../deps/glm/glm/gtc/matrix_transform.hpp"
#include "../deps/glm/glm/gtc/matrix_inverse.hpp"
#include "../deps/glm/glm/gtc/type_ptr.hpp"

// Standard
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <limits.h>
#include <unistd.h>

/*
  FAST GL TUTORIAL:
  VBO = vertex buffer objects, this data is stored on the graphics card
  1. glGenBuffers(int, GLuint) creats a unique id for the GLuint VBO, 
  2. glBindBuffer(data, target) specifies the target, what the VBO will
  be used as. Also any buffer calls  made after this will point to that VBO. 
  3. glBufferData(type, sizeOfData, data, howShouldGLManageData) copies data into
  the currently bound buffer.
    
  Send data to shader.
  1. glVertexAttribPointer(target, sizeOfElement, type, normalizedOrNot, stride, offset), 
  describes the data we are uploading
  2. glEnableVertexAttribArray(int) enables the attribute pointer

  VAO = Vertex array object, ocntains one or several VBO. Note that it contains
  the exact same data, it is the same reference. 
  1. glGenVertexArrays(n, VAOs), generates a VBO object
  2. glBindVertexArray(VAO), bind a vertex array object
  3. Repeat for each VBO, glBindBuffer(type, VAO) bind the data
  4. glEnableVertexAttribArray(index) enables the data at index
  1*/

FlogstaEngine::FlogstaEngine(int choice) {
  printf("Running as %dD engine!\n",choice);
}

FlogstaEngine::~FlogstaEngine(){
  //Destroy window
  SDL_DestroyWindow( window );

  //Quit SDL subsystems
  SDL_Quit();
}


void FlogstaEngine::printCurrentContext(){
  int major, minor, db;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
  SDL_GL_GetAttribute(SDL_GL_DEPTH_SIZE, &db);
  std::cout << "SDL2 OpenGL version: " << major << "." << minor << std::endl << "       depth buffer: " << db << std::endl;
  printf("OpenGL version: %s\n", glGetString(GL_VERSION));
  printf("        vendor: %s\n", glGetString(GL_VENDOR));
  printf("      renderer: %s\n", glGetString(GL_RENDERER));
  printf("  glsl version: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
}


bool FlogstaEngine::init() {
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    fprintf(stderr, "SDL_Init failed with reason: %s\n", strerror(errno));
    return false;
  }

  window = SDL_CreateWindow("Flogsta Engine 0.0.1", SDL_WINDOWPOS_CENTERED,
                            SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                            SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
  if(window == NULL) {
    printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    fprintf(stderr, "SDL_CreateWindow failed with reason: %s\n",
            strerror(errno));
    return false;
  }
    
  SDL_GLContext context = NULL;
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  // SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  // SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);
    
  context = SDL_GL_CreateContext(window);
  printCurrentContext();
  if (context == NULL) {
    fprintf(stderr, "SDL_GLContext context = NULL. Failed with reason: %s\n",
            SDL_GetError());
    return false;
  }

    
  //Create window
    
  screenSurface = SDL_GetWindowSurface( window );

  if (screenSurface == NULL) {
    printf("screenSurface returned null, quitting...\n");
    fprintf(stderr, "SDL_GetWindowSurface failed with reason: %s\n",
            strerror(errno));
    return false;
  }
    
  SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
  SDL_UpdateWindowSurface( window );

  
  glewExperimental = GL_TRUE; 
  if (glewInit()) {
    std::cout << "Glew init failed\n";
    return false;
  }

  std::cout << "glewInit passed\n";
  
  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
  SDL_GL_SetSwapInterval(1);
  
  printCurrentContext();
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
  return true;
}

void FlogstaEngine::drawMesh(Mesh3D mesh) {
  program.enable();
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  GLfloat aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
  // set variables for glm::lookAt
  glm::vec3 position(0.0f, 1.0f, -6.0f);
  glm::vec3 direction(0.0f, 0.0f, 0.0f);
  glm::vec3 up(0.0f, 1.0f, 0.0f);
    
  // Create all necessary matrices
  //glm::mat4 tr = trackball.getRotationMatrix();
  glm::mat4 modelCube = glm::mat4(1.0);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
  view = glm::lookAt(position , direction, up);
  projection = glm::perspective(45.0f, aspect, 0.1f, 100.0f);
  modelCube = glm::rotate(modelCube, glm::radians((GLfloat)SDL_GetTicks())/10.0f, glm::vec3(0.0f, 1.0f, 0.0f));
  // TODO Fix this
  glm::vec3 light_position = glm::vec3(-7.0f,0.0f,7.0f);
  glm::vec3 light_color = glm::vec3(0.7f, 0.7f, 0.7f);
  program.setUniform3f("light_position", light_position);
  program.setUniform3f("light_color", light_color);
  program.setUniform3f("view_pos", position);
    
  glm::vec3 diffuseColor = glm::vec3(0.1f, 0.1f, 0.1f);
  glm::vec3 ambientColor = glm::vec3(0.015f, 0.45f, 0.45f);
  glm::vec3 specularColor = glm::vec3(0.015f, 0.45f, 0.45f);
  //glm::vec3 bgColor = glm::vec3(1.0f, 0.4f, 0.5f);
  glm::vec3 bgColor = glm::vec3(1.0f, 1.0f, 1.0f);
  float specularPower = 40.0f;
    
  // Send all uniform attributes to GPU
  program.setUniformMatrix4f("V", view);
  program.setUniformMatrix4f("P", projection);
  program.setUniformMatrix4f("M", modelCube);
  program.setUniformMatrix4f("ModelView",view * modelCube);
  //program.setUniformMatrix4f("trackball", tr);

  program.setUniform1f("specular_power", specularPower);
  //program.setUniform3f("ambient_color", ambientColor);
  program.setUniform3f("light_color", light_color);
  program.setUniform3f("specular_color", specularColor);
  //  program.setUniform3f("diffuseColor", diffuseColor);
  program.setUniform3f("diffuseColor",  glm::vec3(0.0f,glm::radians((GLfloat)SDL_GetTicks())/10.0f,0.0f));

  
  // Activate VBO and draw
  /*glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
  */
  mesh.bindAndDraw();
  // Disable shader
  program.disable();
}

void FlogstaEngine::swapWindow() {
  SDL_GL_SwapWindow(window);
}

bool FlogstaEngine::setShaderSource(const GLenum type, const std::string &source) {
  program.setShaderSource(type, source);
  return true;
}

bool FlogstaEngine::compileAndLinkShaders() {
  program.update();
  return true;
}

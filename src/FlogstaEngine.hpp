#pragma once

#ifndef FLOGSTAENGINE_H
#define FLOGSTAENGINE_H

#include "Mesh3D.hpp"
#include "ShaderProgram.hpp"
#include "../deps/glm/glm/glm.hpp"
#include "../deps/glm/glm/gtc/matrix_transform.hpp"
#include "../deps/glm/glm/gtc/matrix_inverse.hpp"
#include "../deps/glm/glm/gtc/type_ptr.hpp"

class FlogstaEngine {
private:
  // The attribute locations we will use in the vertex shader
  enum AttributeLocation {
    POSITION = 0,
    NORMAL = 1,
    TEXCOORD = 2,
    TANGENT = 3,
    BITANGENT = 4
  };

  // Screen dimension constants
  const int SCREEN_WIDTH = 640;
  const int SCREEN_HEIGHT = 480;

  SDL_Window* window = NULL;
  SDL_Surface* screenSurface;
  ShaderProgram program;
  
public:
  FlogstaEngine(int choice);
  ~FlogstaEngine();

  void swapWindow();
  bool init();
  void printCurrentContext();

  bool setShaderSource(const GLenum type, const std::string &source);
  bool compileAndLinkShaders();
  void drawMesh(Mesh3D mesh);
};

#endif /* FLOGSTAENGINE_H */

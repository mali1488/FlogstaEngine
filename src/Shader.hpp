/* Copyright (C) 2015 by menuan */

#pragma once

#ifndef SRC_SHADER_H_
#define SRC_SHADER_H_


// #define GLM_FORCE_RADIANS
#define GL_GLEXT_PROTOTYPES
#define GL_PROTOTYPES 1

#include <GL/gl.h>
#include <string>

class Shader {
 private:
  int program;
  int vertexShader;
  int pixelShader;
  char *md5sum;

  const std::string shaderFolder = "./shaders/";
  
  static int textureunit;

 public:
  Shader(const char *vertex, const char *pixel);
  ~Shader();

  int getProgram() { return program; }
  void linkShaders();
  bool loadShader(const char *filename, int type, int &shader);
  void activateShader();
  void loadTexture(const char *filename, const int &texunit);
};

#endif  // SRC_SHADER_H_

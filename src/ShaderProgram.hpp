#pragma once
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <map>

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram();
  bool update();
  void setShaderSource(const GLenum type, const std::string &source);
   
private:
  std::map< GLenum , std::string> shaderSources;
  std::map<std::string, int32_t> attributeLocations;
  bool validProgram;
  uint32_t program;

  // Help functions
  GLuint createShader(GLenum type, const char* shader_source);
  void showShaderInfoLog(GLuint shader);
  void showProgramInfoLog(GLuint program);
  bool validateProgram(GLuint program);
  bool linkProgram(GLuint program);
  std::string readGLSLSource(const std::string &filename);
};


#endif /* SHADERPROGRAM_H */

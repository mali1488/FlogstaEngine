#pragma once
#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <GL/glew.h>
#include <map>
#include "../deps/glm/glm/gtc/type_ptr.hpp"

class ShaderProgram {
public:
  ShaderProgram();
  ~ShaderProgram();
  bool update();
  void setShaderSource(const GLenum type, const std::string &source);

  // Set uniform functions
  bool setUniform1i(const char *name, int value);
  bool setUniform2i(const char *name, glm::ivec2 value);
  bool setUniform3i(const char *name, glm::ivec3 value);
  bool setUniform4i(const char *name, glm::ivec4 value);
  bool setUniform1f(const char *name, float value);
  bool setUniform2f(const char *name, glm::vec2 value);
  bool setUniform3f(const char *name, glm::vec3 value);
  bool setUniform4f(const char *name, glm::vec4 value);
  bool setUniformMatrix2f(const char *name, glm::mat2 value);
  bool setUniformMatrix3f(const char *name, glm::mat3 value);
  bool setUniformMatrix4f(const char *name, glm::mat4 value);
  void enable();
  void disable();
  

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

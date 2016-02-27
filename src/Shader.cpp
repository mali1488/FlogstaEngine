// Copyright (C) 2015 by menuan

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include "Shader.hpp"


Shader::Shader(const char *vertex, const char *pixel) {
  program = -1;
  vertexShader = -1;
  pixelShader = -1;

  if (!loadShader(vertex, GL_VERTEX_SHADER, vertexShader))
    printf("Failed VERTEX shader!\n");
  if (!loadShader(pixel, GL_FRAGMENT_SHADER, pixelShader))
    printf("Failed PIXEL shader!\n");
  linkShaders();
}

Shader::~Shader() {}

bool Shader::loadShader(const char *filename,
                        int type, int &shader) {
  std::string path = shaderFolder;
  path.append(filename);
  shader = glCreateShader(type);
  if (!shader) {
    fprintf(stderr, "[Shader failure #1] glCreateShader returned 0:\t%s\nReason:\t\t%s\n",
            path.c_str(),
            strerror(errno));
    return false;
  }

  std::ifstream shaderfile(path);

  if (!shaderfile.is_open()) {
    fprintf(stderr, "[Shader failure #2] Failed to open shader:\t%s\nReason:\t\t%s\n",
            path.c_str(),
            strerror(errno));
    return false;
  }

  std::ostringstream shaderprogram;
  while (true) {
    char c;
    shaderfile.get(c);
    if (shaderfile.eof())
      break;
    shaderprogram << c;
  }

  std::string s = shaderprogram.str();
  const char *code = s.c_str();

  glShaderSource(shader, 1, &code, NULL);
  glCompileShader(shader);
  int result;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
  if (!result) {
    int logLen;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
    char *log = new char[logLen];
    int written;
    glGetShaderInfoLog(shader, logLen, &written, log);
    fprintf(stderr, "[Shader failure #3] File: %s\n", path.c_str());
    delete [] log;
    return false;
  }
  return true;
}

void Shader::linkShaders() {
  if (program >= 0) {
    glDeleteProgram(program);
  }
  program = glCreateProgram();
  if (!program) {
    return;
  }
  if (vertexShader >= 0) {
    glAttachShader(program, vertexShader);
  }
  if (pixelShader >= 0) {
    glAttachShader(program, pixelShader);
  }
  glLinkProgram(program);
  int result;
  glGetProgramiv(program, GL_LINK_STATUS, &result);
  if (!result) {
    int logLen;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
    char * log = new char[logLen];
    int written;
    glGetProgramInfoLog(program, logLen, &written, log);
    printf("--linkShaders:\n%s\n", log);
    delete [] log;
    return;
  }
}

void Shader::loadTexture(const char *filename, const int &texunit) {}

void Shader::activateShader() {
  if (program >= 0)
    glUseProgram(program);
}

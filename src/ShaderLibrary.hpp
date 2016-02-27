#pragma once

#ifndef SHADERLIBRARY_H
#define SHADERLIBRARY_H

#include <map>

#include "LibIncludes.hpp"
#include "Shader.hpp"

enum ShaderType { vertex, tessctrl, tesseval,
                  geometry, fragment, compute };

class ShaderLibrary {
 private:
  std::map<std::string, Shader&> *vertexShaders;
  std::map<std::string, Shader&> *fragmentShaders;
  

  void loadVertexShaders();
  void loadFragmentShaders();
  
 public:

  ShaderLibrary() {
    this->vertexShaders =
        new std::map<std::string, Shader&>();
    this->fragmentShaders =
        new std::map<std::string, Shader&>();
    loadVertexShaders();
    loadFragmentShaders();
  }
  ~ShaderLibrary() {}

  Shader *getShader(std::pair<ShaderType, std::string> &pID) {
    std::map<std::string, Shader&>::iterator it;
    switch (pID.first) {
      case vertex:
        printf("Trying to fetch a vertex shader!\n");
        it =
            this->vertexShaders->find(pID.second);
        if (it != this->vertexShaders->end())
          return &(it->second);
      case fragment:
        printf("Trying to fetch a fragment shader!\n");
        it =
            this->fragmentShaders->find(pID.second);
        if (it != this->fragmentShaders->end())
          return &(it->second);
      default:
        printf("Unsupported type %d\n", pID.first);
        return nullptr;
    }
  }
  
};


#endif /* SHADERLIBRARY_H */

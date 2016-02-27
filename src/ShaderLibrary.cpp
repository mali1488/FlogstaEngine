#include "ShaderLibrary.hpp"

void ShaderLibrary::loadVertexShaders( ){
  static const std::string folder = "../assets/shaders/";
  static const std::string vrtxShdrs[] = {"vertexshader.vert"};
  int l = 1;
  printf("<ShaderLibrary> loadVertexShaders\n");
  for (int i = 0; i < l; i++) {
    std::string target = folder + vrtxShdrs[i];
    printf("%s\n", target.c_str());
  }
}

void ShaderLibrary::loadFragmentShaders( ){
  
}

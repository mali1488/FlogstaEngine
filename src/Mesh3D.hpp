#pragma once

#ifndef MESH3D_H
#define MESH3D_H

#include <string>
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include "../deps/glm/glm/glm.hpp"
#include <vector>
#include "OBJFileReader.hpp"

typedef struct Vertex {
  float position[3];
  float normal[3];
  float st[2];
} Vertex;

class Mesh3D {
public:
  Mesh3D();
  ~Mesh3D();

  bool loadMesh(const std::string &filename, int n);
  bool createMeshVAO();
  void bindAndDraw();

private:
  // Mesh data, VBO
  std::vector<glm::vec3> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec2> uvs;
  std::vector<glm::vec2> uvsOriginal;
  std::vector<glm::vec3> tangents;
  std::vector<glm::vec3> bitangents;
  std::vector<uint32_t> indices;
  std::vector<uint32_t> uvIndices;
  std::vector<GLfloat> fvertices;
  std::vector<GLfloat> fuv;

  // MeshVAO data, VAO
  GLuint vao;
  GLuint vertexVBO;
  GLuint normalVBO;
  GLuint indexVBO;
  GLuint texCoordVBO;
  GLuint tangetsVBO;
  GLuint bitangentVBO;
  int numVertices;
  int numIndices;
  int numUv;  
};


#endif /* MESH3D_H */

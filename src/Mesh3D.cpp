#include "Mesh3D.hpp"

Mesh3D::Mesh3D() {}

Mesh3D::~Mesh3D() {
  glDeleteVertexArrays(1, &(vertexVBO));
  glDeleteVertexArrays(1, &(normalVBO));
}

bool Mesh3D::loadMesh(const std::string &filename, int n) {
  OBJFileReader reader;
  reader.load(filename.c_str(),n);
  vertices = reader.getVertices();
  normals = reader.getNormals();
  indices = reader.getIndices();
  uvs = reader.getUvs();
  fuv = reader.getFloatUvs();
  fvertices = reader.getFloatVectices();
  uvIndices = reader.getUvIndices();
  uvsOriginal = reader.getUvsOriginal();

  // Do this for certain objects with bitangents and tangets
  //computeTangentBitangent(mesh);
}

bool Mesh3D::createMeshVAO() {
  // Generates a VBO, data buffer for the GPU
  glGenBuffers(1, &(texCoordVBO));
  glBindBuffer(GL_ARRAY_BUFFER, texCoordVBO);
  auto UVBytes = uvs.size() * sizeof(uvs[0]);
  glBufferData(GL_ARRAY_BUFFER, UVBytes, uvs.data() , GL_STATIC_DRAW);
    
  // Generates and populates a VBO for the vertices
  glGenBuffers(1, &(vertexVBO));
  glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
  auto verticesNBytes = vertices.size() * sizeof(vertices[0]);
  glBufferData(GL_ARRAY_BUFFER, verticesNBytes, vertices.data(), GL_STATIC_DRAW);
    
  // Generates and populates a VBO for the vertex normals
  glGenBuffers(1, &(normalVBO));
  glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
  auto normalsNBytes = normals.size() * sizeof(normals[0]);
  glBufferData(GL_ARRAY_BUFFER, normalsNBytes, normals.data(), GL_STATIC_DRAW);
        
  // Generates and populates a VBO for the element indices
  glGenBuffers(1, &(indexVBO));
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
  auto indicesNBytes = indices.size() * sizeof(indices[0]);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesNBytes, indices.data(), GL_STATIC_DRAW);

  // Creates a vertex array object (VAO) for drawing the mesh
  glGenVertexArrays(1, &(vao));
  glBindVertexArray(vao);
    
  /*   
       glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
       glEnableVertexAttribArray(POSITION);
       glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
       glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
       glEnableVertexAttribArray(NORMAL);
       glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);
  */
  glBindBuffer(GL_ARRAY_BUFFER, vertexVBO);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
  glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
  /*glBindBuffer(GL_ARRAY_BUFFER, bitangentVBO);
    glEnableVertexAttribArray(BITANGENT);
    glVertexAttribPointer(BITANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);
  */
    
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexVBO);
  glBindVertexArray(0); // unbinds the VAO
    
  // Additional information required by draw calls
  numVertices = vertices.size();
  numIndices = indices.size();
}
  
void Mesh3D::bindAndDraw() {
  // Activate VBO and draw
  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}

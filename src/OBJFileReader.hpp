#pragma once

#ifndef OBJFILEREADER_H
#define OBJFILEREADER_H

#include "../deps/glm/glm/glm.hpp"
#include <stdint.h>
#include <vector>
#include <GL/glew.h>

class OBJFileReader {
public:
  OBJFileReader();
  ~OBJFileReader();
        
  // Execute the reader.
  bool load(const char *filename, int n);
        
  // Get the vertices of the 3D model.
  std::vector<glm::vec3> const &getVertices() const;
        
  // Get the per-vertex normals of the 3D model.
  std::vector<glm::vec3> const &getNormals() const;
        
  // Get the element indices of the 3D model.
  std::vector<uint32_t> const &getIndices() const;
        
  std::vector<glm::vec2> const &getUvs() const;
  std::vector<GLfloat> const &getFloatVectices() const;
  std::vector<GLfloat> const &getFloatUvs() const;
  std::vector<uint32_t> const &getUvIndices() const;
  std::vector<glm::vec2> const &getUvsOriginal() const;
        
private:
  std::vector<glm::vec3> mVertices;
  std::vector<glm::vec3> mNormals;
  std::vector<glm::vec2> mUv;
  std::vector<glm::vec2> uvsOriginal;
        
  std::vector<uint32_t> mIndices;
  std::vector<uint32_t> mUvIndices;
  std::vector<uint32_t> mNormalIndices;
  std::vector<float> fVertices;
  std::vector<float> fUvs;
        
};

#endif /* OBJFILEREADER_H */

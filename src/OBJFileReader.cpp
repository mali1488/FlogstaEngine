#include "OBJFileReader.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

// Unnamed namespace (for helper functions and constants)
namespace {
  const std::string VERTEX_LINE("v ");
  const std::string FACE_LINE("f ");
  const std::string UV_LINE("vt");

  void computeNormals(std::vector<glm::vec3> const &vertices, std::vector<uint32_t> const &indices, std::vector<glm::vec3> &normals) {
    normals.resize(vertices.size(), glm::vec3(0.0f, 0.0f, 0.0f));
        
    // Compute per-vertex normals by averaging the unnormalized face normals
    uint32_t vertexIndex0, vertexIndex1, vertexIndex2;
    glm::vec3 normal;
    size_t numIndices = indices.size();
    for (int i = 0; i < numIndices; i += 3) {
      vertexIndex0 = indices[i];
      vertexIndex1 = indices[i + 1];
      vertexIndex2 = indices[i + 2];
      normal = glm::cross(vertices[vertexIndex1] - vertices[vertexIndex0],
			  vertices[vertexIndex2] - vertices[vertexIndex0]);
      normals[vertexIndex0] += normal;
      normals[vertexIndex1] += normal;
      normals[vertexIndex2] += normal;
    }
        
    size_t numNormals = normals.size();
    for (int i = 0; i < numNormals; i++) {
      normals[i] = glm::normalize(normals[i]);
    }
  }
}

struct MeshFaceIndex {
  int pos_index[3];
  int tex_index[3];
  int nor_index[3];
};

OBJFileReader::OBJFileReader()
  : mVertices(0), mNormals(0), mIndices(0) {
  std::cout << "Called OBJFileReader constructor" << std::endl;
}

OBJFileReader::~OBJFileReader() {}

bool OBJFileReader::load(const char *filename, int n) {
  // Open OBJ file
  std::ifstream OBJFile(filename);
  std::cout << "trying to load obj" << std::endl;
  // Original load
  if(n==1) {
    if (!OBJFile.is_open()) {
      std::cerr << "Could not open " << filename << std::endl;
      return false;
    }
        
    // Extract vertices and indices
    std::string line;
    glm::vec3 vertex;
    uint32_t vertexIndex0, vertexIndex1, vertexIndex2;
    while (!OBJFile.eof()) {
      std::getline(OBJFile, line);
      if (line.substr(0, 2) == VERTEX_LINE) {
	std::istringstream vertexLine(line.substr(2));
	vertexLine >> vertex.x;
	vertexLine >> vertex.y;
	vertexLine >> vertex.z;
	mVertices.push_back(vertex);
      }
      else if (line.substr(0, 2) == FACE_LINE) {
	std::istringstream faceLine(line.substr(2));
	faceLine >> vertexIndex0;
	faceLine >> vertexIndex1;
	faceLine >> vertexIndex2;
	mIndices.push_back(vertexIndex0 - 1);
	mIndices.push_back(vertexIndex1 - 1);
	mIndices.push_back(vertexIndex2 - 1);
      }
      else {
	//std::cout << "strange line: " << line << std::endl;
	// Ignore line
      }
    }
    std::cout << "close obj reader file\n";
    // Close OBJ file
    OBJFile.close();
        
    // Compute normals
    computeNormals(mVertices, mIndices, mNormals);
        
    // Display log message
    std::cout << "Loaded OBJ file " << filename << std::endl;
    size_t numTriangles = mIndices.size() / 3;
    std::cout << "Number of triangles: " << numTriangles << std::endl;
        
    return true;
  }
    
  // Loading wavefront file with three face elements and has three data i each element => f v/vt/vn v/vt/vn v/vt/vn
  if (n == 3 || n == 4) {
    if (!OBJFile.is_open()) {
      std::cerr << "Could not open " << filename << std::endl;
      return false;
    }
        
    // Extract vertices and indices
    std::string line;
    glm::vec3 vertex;
    uint32_t vertexIndex0, vertexIndex1, vertexIndex2;
    std::vector<glm::vec3> temp_vertices;
    std::vector<glm::vec2> temp_uv;
        
    while (!OBJFile.eof()) {
      std::getline(OBJFile, line);
            
      if (line.substr(0, 2) == VERTEX_LINE) {
	//std::cout << "vertex line" << std::endl;
	std::istringstream vertexLine(line.substr(2));
	vertexLine >> vertex.x;
	vertexLine >> vertex.y;
	vertexLine >> vertex.z;
	temp_vertices.push_back(vertex);
	mVertices.push_back(vertex);
      }
      else if (line.substr(0, 2) == FACE_LINE) {
	if(n == 1) {
	  std::istringstream faceLine(line.substr(2));
	  faceLine >> vertexIndex0;
	  faceLine >> vertexIndex1;
	  faceLine >> vertexIndex2;
	  mIndices.push_back(vertexIndex0 - 1);
	  mIndices.push_back(vertexIndex1 - 1);
	  mIndices.push_back(vertexIndex2 - 1);
	} else if (n == 3) {
	  int vectorIndex, UvIndex, normalIndex;
                    
	  std::istringstream faceLine(line.substr(2));
	  std::string tempFaceline;
                    
	  size_t pos;
	  std::string delimiter = "/";
	  std::string temp;
                    
	  for(int i = 0; i < 3; i++) {
	    // Take out the face
	    faceLine >> tempFaceline;
                        
	    // Get vertex index
	    pos = tempFaceline.find(delimiter);
	    temp = tempFaceline.substr(0,pos);
	    vectorIndex = std::stoi(temp)-1;
	    mIndices.push_back(vectorIndex);
	    tempFaceline = tempFaceline.substr(pos + 1, tempFaceline.size());
                        
	    // Get UV index
	    pos = tempFaceline.find(delimiter);
	    temp = tempFaceline.substr(0,pos);
	    UvIndex = std::stoi(temp)-1;
	    mUvIndices.push_back(UvIndex);
	    tempFaceline = tempFaceline.substr(pos + 1, tempFaceline.size());
                        
	    // Get normal index
	    temp = tempFaceline.substr(0,tempFaceline.size());
	    normalIndex = std::stoi(temp)-1;
	    mNormalIndices.push_back(normalIndex);
	  }
	} else if (n == 4) {
	  int vectorIndex, UvIndex, normalIndex;
                    
	  std::istringstream faceLine(line.substr(2));
	  std::string tempFaceline;
                    
	  size_t pos;
	  std::string delimiter = "/";
	  std::string temp;

	  //std::cout << line.substr(2) << std::endl;
	  for(int i = 0; i < 4; i++) {
	    // Take out the face
	    faceLine >> tempFaceline;
	    //std::cout << tempFaceline << std::endl;

	    // Get vertex index
	    pos = tempFaceline.find(delimiter);
	    temp = tempFaceline.substr(0,pos);
	    vectorIndex = std::stoi(temp)-1;
	    mIndices.push_back(vectorIndex);
	    tempFaceline = tempFaceline.substr(pos + 1, tempFaceline.size());

	    // TODO This should be checked everywhere
	    if (tempFaceline.substr(0,1) == "/") {
	      tempFaceline = tempFaceline.substr(1, tempFaceline.size());
	      // Get normal index
	      temp = tempFaceline.substr(0,tempFaceline.size());
	      normalIndex = std::stoi(temp)-1;
	      mNormalIndices.push_back(normalIndex);
	    } else {

	    // Get UV index
	    pos = tempFaceline.find(delimiter);
	    temp = tempFaceline.substr(0,pos);
	    UvIndex = std::stoi(temp)-1;
	    mUvIndices.push_back(UvIndex);
	    tempFaceline = tempFaceline.substr(pos + 1, tempFaceline.size());
	    
	    // Get normal index
	    temp = tempFaceline.substr(0,tempFaceline.size());
	    normalIndex = std::stoi(temp)-1;
	    mNormalIndices.push_back(normalIndex);
	    }
	  }
	}
      } else if (line.substr(0, 2) == UV_LINE) {
	std::string uvLine = line.substr(3);
	size_t pos = uvLine.find(" ");
	std::string temp = uvLine.substr(0,pos);
	glm::vec2 uv;
	uv.x = std::atof(temp.c_str());
                
	uvLine = uvLine.substr(pos,uvLine.size());
	temp = uvLine.substr(0,uvLine.size());
	uv.y = std::atof(temp.c_str());
	temp_uv.push_back(uv);
      }
    }

    // Close OBJ file
    OBJFile.close();
    // Compute normals
    computeNormals(mVertices, mIndices, mNormals);
        
    // Garage hack to initialize the uv vector
    for(int i = 0; i < mIndices.size(); i++) {
      mUv.push_back(glm::vec2 (0.0,0.0));
    }
        
    // Place all the UVs to corresponding vertex
    // This is needed because the VBO does not support obj indices
    // In other words, place the data right so the VBO send the right data
    for(int i = 0; i < mIndices.size(); i ++) {
      mUv[mIndices[i]] = temp_uv[mUvIndices[i]];
    }
    uvsOriginal = temp_uv;
    std::cout << "Loaded OBJ file " << filename << std::endl;
    size_t numTriangles = mIndices.size() / 3;
    std::cout << "Number of triangles: " << numTriangles << std::endl;
    return true;
  }
  return false;
}

std::vector<glm::vec3> const &OBJFileReader::getVertices() const {
  return mVertices;
}

std::vector<glm::vec3> const &OBJFileReader::getNormals() const {
  return mNormals;
}

std::vector<glm::vec2> const &OBJFileReader::getUvs() const {
  return mUv;
}

std::vector<uint32_t> const &OBJFileReader::getIndices() const {
  return mIndices;
}

std::vector<uint32_t> const &OBJFileReader::getUvIndices() const {
  return mUvIndices;
}

std::vector<glm::vec2> const &OBJFileReader::getUvsOriginal() const {
  return uvsOriginal;
}

std::vector<GLfloat> const &OBJFileReader::getFloatVectices() const {
  return fVertices;
}
std::vector<GLfloat> const &OBJFileReader::getFloatUvs() const {
  return fUvs;
}

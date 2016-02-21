#include "LibIncludes.hpp"
#include "FeEventHandler.hpp"
#include "OBJFileReader.hpp"
#include "ShaderProgram.hpp"
// Deps
#include "../deps/glm/glm/glm.hpp"
#include "../deps/glm/glm/gtc/matrix_transform.hpp"
#include "../deps/glm/glm/gtc/matrix_inverse.hpp"
#include "../deps/glm/glm/gtc/type_ptr.hpp"
// Standard
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <limits.h>
#include <unistd.h>
/*
  FAST GL TUTORIAL:
  VBO = vertex buffer objects, this data is stored on the graphics card
    1. glGenBuffers(int, GLuint) creats a unique id for the GLuint VBO, 
    2. glBindBuffer(data, target) specifies the target, what the VBO will
       be used as. Also any buffer calls  made after this will point to that VBO. 
    3. glBufferData(type, sizeOfData, data, howShouldGLManageData) copies data into
       the currently bound buffer.
    
   Send data to shader.
     1. glVertexAttribPointer(target, sizeOfElement, type, normalizedOrNot, stride, offset)
    

*/


// The attribute locations we will use in the vertex shader
enum AttributeLocation {
    POSITION = 0,
    NORMAL = 1,
    TEXCOORD = 2,
    TANGENT = 3,
    BITANGENT = 4
};


// Struct for representing an indexed triangle mesh
struct Mesh {
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
};

// Struct for represents a vertex array object (VAO) created from a
// mesh. Used for rendering.
struct MeshVAO {
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

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

ShaderProgram p;
SDL_Window* window = NULL;
SDL_Surface* screenSurface;
MeshVAO meshVAO;
Mesh mesh;

float zoom = 0.0f;
float r = 0.0;
float angle = 0.0;

void printCurrentContext(){
  int major, minor;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
  std::cout << "Got OpenGL " << major << "." << minor << std::endl;
  std::cout << "Shader GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
}

void init() {
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  } else {
    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
    
    if( window == NULL ) {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    } else {
      screenSurface = SDL_GetWindowSurface( window );
      SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
      SDL_UpdateWindowSurface( window );
  
    }
  }
  glewExperimental = GL_TRUE; 
  if (glewInit()) {
    std::cout << "Glew init failed\n";
    exit(0);
  }

  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
  SDL_GL_SetSwapInterval(1);
  
  printCurrentContext();
}

void loadMesh(const std::string &filename, Mesh *mesh, int n) {
    OBJFileReader reader;
    reader.load(filename.c_str(),n);
    mesh->vertices = reader.getVertices();
    mesh->normals = reader.getNormals();
    mesh->indices = reader.getIndices();
    mesh->uvs = reader.getUvs();
    mesh->fuv = reader.getFloatUvs();
    mesh->fvertices = reader.getFloatVectices();
    mesh->uvIndices = reader.getUvIndices();
    mesh->uvsOriginal = reader.getUvsOriginal();
    //computeTangentBitangent(mesh);
}

void createMeshVAO(const Mesh &mesh, MeshVAO *meshVAO) {
    // Generates a VBO, data buffer for the GPU
    glGenBuffers(1, &(meshVAO->texCoordVBO));
    glBindBuffer(GL_ARRAY_BUFFER, meshVAO->texCoordVBO);
    auto UVBytes = mesh.uvs.size() * sizeof(mesh.uvs[0]);
    glBufferData(GL_ARRAY_BUFFER, UVBytes, mesh.uvs.data() , GL_STATIC_DRAW);
    
    // Generates and populates a VBO for the vertices
    glGenBuffers(1, &(meshVAO->vertexVBO));
    glBindBuffer(GL_ARRAY_BUFFER, meshVAO->vertexVBO);
    auto verticesNBytes = mesh.vertices.size() * sizeof(mesh.vertices[0]);
    glBufferData(GL_ARRAY_BUFFER, verticesNBytes, mesh.vertices.data(), GL_STATIC_DRAW);
    
    // Generates and populates a VBO for the vertex normals
    glGenBuffers(1, &(meshVAO->normalVBO));
    glBindBuffer(GL_ARRAY_BUFFER, meshVAO->normalVBO);
    auto normalsNBytes = mesh.normals.size() * sizeof(mesh.normals[0]);
    glBufferData(GL_ARRAY_BUFFER, normalsNBytes, mesh.normals.data(), GL_STATIC_DRAW);
        
    // Generates and populates a VBO for the element indices
    glGenBuffers(1, &(meshVAO->indexVBO));
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshVAO->indexVBO);
    auto indicesNBytes = mesh.indices.size() * sizeof(mesh.indices[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicesNBytes, mesh.indices.data(), GL_STATIC_DRAW);

    // Creates a vertex array object (VAO) for drawing the mesh
    glGenVertexArrays(1, &(meshVAO->vao));
    glBindVertexArray(meshVAO->vao);
    
    glBindBuffer(GL_ARRAY_BUFFER, meshVAO->vertexVBO);
    glEnableVertexAttribArray(POSITION);
    glVertexAttribPointer(POSITION, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, meshVAO->normalVBO);
    glEnableVertexAttribArray(NORMAL);
    glVertexAttribPointer(NORMAL, 3, GL_FLOAT, GL_FALSE, 0, 0);

    /*glBindBuffer(GL_ARRAY_BUFFER, meshVAO->bitangentVBO);
    glEnableVertexAttribArray(BITANGENT);
    glVertexAttribPointer(BITANGENT, 3, GL_FLOAT, GL_FALSE, 0, 0);
    */
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshVAO->indexVBO);
    glBindVertexArray(0); // unbinds the VAO
    
    // Additional information required by draw calls
    meshVAO->numVertices = mesh.vertices.size();
    meshVAO->numIndices = mesh.indices.size();
}

void drawMesh(ShaderProgram &program, const MeshVAO &meshVAO) {
  program.enable();
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  GLfloat aspect = SCREEN_WIDTH / SCREEN_HEIGHT;
  // set variables for glm::lookAt
  glm::vec3 position(0.0f, 1.0f, -6.0f);
  glm::vec3 direction(0.0f, 0.0f, 0.0f);
  glm::vec3 up(0.0f, 1.0f, 0.0f);
    
  // Create all necessary matrices
  //glm::mat4 tr = trackball.getRotationMatrix();
  glm::mat4 modelCube = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 projection = glm::mat4(1.0f);
  view = glm::lookAt(position , direction, up);
  projection = glm::perspective(45.0f + zoom, aspect, 0.1f, 100.0f);
  
  // TODO Fix this
  glm::vec3 light_position = glm::vec3(-7.0f,0.0f,7.0f);
  glm::vec3 light_color = glm::vec3(0.7f, 0.7f, 0.7f);
  program.setUniform3f("light_position", light_position);
  program.setUniform3f("light_color", light_color);
  program.setUniform3f("view_pos", position);
    
  glm::vec3 diffuseColor = glm::vec3(0.1f, 0.1f, 0.1f);
  glm::vec3 ambientColor = glm::vec3(0.015f, 0.45f, 0.45f);
  glm::vec3 specularColor = glm::vec3(0.015f, 0.45f, 0.45f);
  //glm::vec3 bgColor = glm::vec3(1.0f, 0.4f, 0.5f);
  glm::vec3 bgColor = glm::vec3(1.0f, 1.0f, 1.0f);
  float specularPower = 40.0f;
    
  // Send all uniform attributes to GPU
  program.setUniformMatrix4f("V", view);
  program.setUniformMatrix4f("P", projection);
  program.setUniformMatrix4f("M", modelCube);
  program.setUniformMatrix4f("ModelView",view * modelCube);
  //program.setUniformMatrix4f("trackball", tr);

  program.setUniform1f("specular_power", specularPower);
  //program.setUniform3f("ambient_color", ambientColor);
  program.setUniform3f("light_color", light_color);
  program.setUniform3f("specular_color", specularColor);
  //  program.setUniform3f("diffuseColor", diffuseColor);
  program.setUniform3f("diffuseColor",  glm::vec3(r,r,r));

  
  // Activate VBO and draw
  glBindVertexArray(meshVAO.vao);
  glDrawElements(GL_TRIANGLES, meshVAO.numIndices, GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
  // Disable shader
  program.disable();}

int main(int argc, char *argv[]) {

  init();
  glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  // compile and link shader program
  p.setShaderSource(GL_VERTEX_SHADER,"../assets/shaders/normalMapping.vert");
  p.setShaderSource(GL_FRAGMENT_SHADER,"../assets/shaders/normalMapping.frag");
  p.update();

  // Load a mesh
  loadMesh("../assets/mesh/bunny.obj",&mesh , 1);
  createMeshVAO(mesh, &meshVAO);

  bool quit = false;
  SDL_Event e;  

  while(!quit) {
    while( SDL_PollEvent( &e ) != 0 ){ //User requests quit
      switch(e.type) {
      case SDL_QUIT:
        puts("QUIT FÖR FANOAN");
	quit = true;
	break;
      case SDL_KEYDOWN:
	switch(e.key.keysym.sym) {
	case SDLK_e:
	  printf("eeeee\n");
	  break;
	case SDLK_q:
          SDL_Event sdlEvent;
          sdlEvent.type = SDL_QUIT;
          SDL_PushEvent(&sdlEvent);
          break;
	}
	break;
      }
    }

    r = (sin(angle) + 0.01)/2;
    drawMesh(p, meshVAO);
    SDL_GL_SwapWindow(window);
    angle+=0.01;

  }

  //Destroy window
  SDL_DestroyWindow( window );
  //Quit SDL subsystems
  SDL_Quit();
  return 0;
}

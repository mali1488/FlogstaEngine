#include "LibIncludes.hpp"
#include "FeEventHandler.hpp"
#include "OBJFileReader.hpp"

// Deps
#include "../deps/glm/glm/glm.hpp"

// Standard
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <limits.h>
#include <unistd.h>
// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
SDL_Renderer* renderer;

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

void loadMeshTest(const std::string &filename, Mesh *mesh, int n) {
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
}

void printCurrentContext(){
  int major, minor;
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &major);
  SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &minor);
  std::cout << "Got OpenGL " << major << "." << minor << std::endl;
}

void render() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main(int argc, char *argv[]) {
  SDL_Window* window = NULL;
  SDL_Surface* screenSurface = NULL;
  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  } else {
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

  bool quit = false;
  SDL_Event e;

  SDL_GLContext context = SDL_GL_CreateContext(window);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

  printCurrentContext();

  glClearDepth(1.0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glClearColor(0.0f, 0.2f, 0.4f, 1.0f);
  SDL_GL_SetSwapInterval(1);
  // Try and loading a mesh from assets. The earthfix object
  // has 3 face elements. Thas is why loadMesh is called with
  // third argument 3. 
  Mesh meshEarth;
  loadMeshTest("../assets/mesh/earthfix.obj" ,&meshEarth,3);
  float r = 0.0;
  float angle = 0.0;
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

    r = (sin(angle) + 1.0)/2;
    
    glClearColor ( r, 0.5, 0.5, 1.0 );
    glClear ( GL_COLOR_BUFFER_BIT );
    SDL_GL_SwapWindow(window);
    angle+=0.1;

  }
  //Destroy window
  SDL_DestroyWindow( window );
  //Quit SDL subsystems
  SDL_Quit();
  return 0;
}

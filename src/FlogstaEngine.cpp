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

std::string getexepath() {
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}

int main(int argc, char *argv[]) {
  FeEventHandler fe;
  glm::vec3 T = glm::vec3(1.0f); 
  printf("Vec3 test: %f, %f, %f\n",T[0],T[1],T[2]);

  // Try and loading a mesh from assets. The earthfix object
  // has 3 face elements. Thas is why loadMesh is called with
  // third argument 3. 
  std::string s = "../assets/mesh/earthfix.obj";
  std::cout << s << std::endl;
  Mesh meshEarth;
  loadMeshTest(s ,&meshEarth,3);
  
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
  }
  //Destroy window
  SDL_DestroyWindow( window );
  //Quit SDL subsystems
  SDL_Quit();
  return 0;
}

#include "LibIncludes.hpp"
#include "FeEventHandler.hpp"
#include "FlogstaEngine.hpp"
#include "Mesh3D.hpp"

// Standard
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <string>
#include <limits.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

  FlogstaEngine FE(3);
  if (FE.init() == false) {
    printf("Could not initialise the engine...\n");
    return 1;
  }
  Mesh3D mesh3d;

  // compile and link shader program
  FE.setShaderSource(GL_VERTEX_SHADER,"../assets/shaders/normalMapping.vert");
  FE.setShaderSource(GL_FRAGMENT_SHADER,"../assets/shaders/normalMapping.frag");
  FE.compileAndLinkShaders();

  // Load a mesh
  mesh3d.loadMesh("../assets/mesh/bunny.obj",1);
  mesh3d.createMeshVAO();
  
  bool quit = false;
  SDL_Event e;  
  FeEventHandler eh(quit);
  while(!quit) {
    eh.pollEvents();
    FE.drawMesh(mesh3d);
    FE.swapWindow();
  }

  return 0;
}

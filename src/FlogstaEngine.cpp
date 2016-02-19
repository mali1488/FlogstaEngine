#include "LibIncludes.hpp"
#include "FeEventHandler.hpp"
#include "../deps/glm/glm/glm.hpp"
#include <stdio.h>
#include <stdlib.h>

//Screen dimension constants

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

int main(int argc, char *argv[]) {
  FeEventHandler fe;
  glm::vec3 T = glm::vec3(1.0f); 
  printf("Vec3 test: %f, %f, %f\n",T[0],T[1],T[2]);
  
  //The window we'll be rendering to
  SDL_Window* window = NULL;

  //The surface contained by the window
  SDL_Surface* screenSurface = NULL;
  
  //Initialize SDL

  if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
  } else {
    //Create window
    window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );

    if( window == NULL ) {
      printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
    } else {
      //Get window surface
      screenSurface = SDL_GetWindowSurface( window );
      //Fill the surface white
      SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
      //Update the surface
      SDL_UpdateWindowSurface( window );
      //Wait two seconds
    }
  }
  //Main loop flag
  bool quit = false;
  
  //Event handler
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

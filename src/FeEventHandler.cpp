#include "FeEventHandler.hpp"

FeEventHandler::FeEventHandler(bool& quit) :
  quit(quit) {
  printf("FeEventHandler constructed!\n");
}

FeEventHandler::~FeEventHandler() {}

void FeEventHandler::pollEvents() {
  while( SDL_PollEvent( &e ) != 0 ){ //User requests quit
    switch(e.type) {
    case SDL_QUIT:
      puts("Quit!");
      quit = true;
      break;
    case SDL_KEYDOWN:
      switch(e.key.keysym.sym) {
      case SDLK_e:
	printf("pressed e\n");
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

#pragma once

#ifndef FEEVENTHANDLER_H
#define FEEVENTHANDLER_H

#include <iostream>
#include <stdio.h>
#include "LibIncludes.hpp"

class FeEventHandler {
private:
  SDL_Event e;
  bool &quit;

public:
  FeEventHandler(bool& quit);
  ~FeEventHandler();

  void pollEvents();
};

#endif /* FEEVENTHANDLER_H */

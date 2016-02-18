#pragma once

#ifndef LIBINCLUDES_H
#define LIBINCLUDES_H

  #if defined MACOSX
    #include <OpenGL/glew.h>
  #elif defined LINUX
    #include <GL/glew.h>
  #endif
  #include <SDL.h>


#endif /* LIBINCLUDES_H */

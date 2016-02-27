#pragma once

#ifndef LIBINCLUDES_H
#define LIBINCLUDES_H

  #if defined MACOSX
    #include <OpenGL/glew.h>
  #elif defined LINUX
    #include <GL/glew.h>
    #include <GL/gl.h>
  #endif
  #include <SDL.h>

#include <string>

#define _USE_MATH_DEFINES 1
#include <math.h>
#define GLM_FORCE_RADIANS
#include "../deps/glm/glm/glm.hpp"
// using glm::mat4;
// using glm::mat3;
// using glm::vec4;
// using glm::vec3;
#include "../deps/glm/glm/gtc/matrix_transform.hpp"
#include "../deps/glm/glm/gtc/matrix_inverse.hpp"


#endif /* LIBINCLUDES_H */

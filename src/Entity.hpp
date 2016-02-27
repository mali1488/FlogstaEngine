#pragma once

#ifndef ENTITY_H
#define ENTITY_H

#include "LibIncludes.h"

class Entity {
 private:

 protected:  
  
 public:
  Entity *parent = NULL;
  glm::vec3 pos;
  glm::vec3 forward;
  glm::vec3 up;

  Entity(glm::vec3 pos, glm::vec3 forward, glm::vec3 up)
      : pos(pos), forward(forward), up(up) {}
  Entity();
  ~Entity();

  glm::mat4 getViewMatrix() {
    up = glm::normalize(up);
    forward = glm::normalize(forward);
    vec3 side = glm::cross(up, forward);
    mat4 rotn = mat4(side.x, up.x, -forward.x, 0.0,
                     side.y, up.y, -forward.y, 0.0,
                     side.z, up.z, -forward.z, 0.0,
                     0.0, 0.0, 0.0, 1.0);
    mat4 tranln = glm::translate(mat4(1.0f),
                                 vec3(-pos.x,
                                      -pos.y,
                                      -pos.z));
    return rotn * tranln;
  }

  glm::mat4 getWorldTransform() {
    vec3 side = glm::cross(up, forward);
    // in this format, goes in as these transpose.
    mat4 rot = mat4(side[0], up[0], forward[0], 0.0,
                    side[1], up[1], forward[1], 0.0,
                    side[2], up[2], forward[2], 0.0,
                    0.0, 0.0, 0.0, 1.0);
    mat4 M = glm::translate(mat4(1.0f),
                            pos) *
        rot * glm::scale(mat4(1.0f), vec3(1.0f / 3.0f));
    return M;
  }

  /* Don't know whether or not we actually need this yet */
  
  // mat3 rotationMatrix(float ux, float uy, float uz, float angle) {
  //   // http://en.wikipedia.org/wiki/Rotation_matrix
  //   float ct = cos(angle);
  //   float st = sin(angle);
  //   float oct = 1.0f - ct;
  //   // float ost = 1.0f - st;
  //   mat3 rot = mat3(ct + ux * ux * oct, ux * uy * oct -
  //                   uz * st, ux * uz * oct + uy * st,
  //                   uy * ux * oct + uz * st, ct + uy *
  //                   uy * oct, uy * uz * oct - ux * st,
  //                   uz * ux * oct - uy * st, uz * uy *
  //                   oct + ux * st, ct + uz * uz * oct);
  //   return rot;
  // }

};

#endif /* ENTITY_H */

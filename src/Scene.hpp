#pragma once

#ifndef SCENE_H
#define SCENE_H

#include <map>
#include <string>
#include <iostream>

#include "LibIncludes.h"
#include "Entity.hpp"
#include "PhysicalEntity.hpp"

struct strLessComp() {
  bool operator()(const std::string &a, const std::string &b) {
    return std::strcmp(a.c_str(), b.c_str()) < 0;
  }
};

class Scene {
 private:
  std::map<std::string& , PhysicalEntity&, strLessComp > *physicalEntities = nullptr;

 public:
  Scene();
  ~Scene();

  bool attachPhysicalEntity(PhysicalEntity &pEntity);
  bool detachPhysicalEntity(Entity &pEntity);
  bool attachEntity(Entity &pEntity);
  bool detachEntity(Entity &pEntity);
};

#endif /* SCENE_H */

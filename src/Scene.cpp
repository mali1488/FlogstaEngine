

#include "Scene.hpp"
#include "Entity.hpp"
#include "PhysicalEntity.hpp"


Scene::Scene() {
  this->physicalEntities = new std::map<std::string, PhysicalEntity&, strLessComp>();
}

Scene::~Scene() {
  delete this->physicalEntities;
}

bool Scene::attachPhysicalEntity(std::string &pName, PhysicalEntity &pEntity) {
  std::pair<std::string, PhysicalEntity&> &newPair =
      new std::pair<std::string, PhysicalEntity&>(pName, pEntity);
  ret = this->physicalEntities->insert(newPair);
  if (ret.second == false) {
    std::cout << "PhysEntity with name " << pName << " already exists.\nExisting PhysicalEntity&: "
              << ret.first->second << "\nTried to store: " << pEntity << std::endl;
    return false;
  }
  return true;
}

bool Scene::detachPhysicalEntity(std::string &pName) {

}

bool Scene::attachEntity(std::string& pName, Entity &pEntity) {

}


bool Scene::detachEntity(std::string &pName) {

}

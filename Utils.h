#pragma once

#include <horde3d/Horde3D.h>
#include "EntitySystem.h"

class Utils
{
public:
  Utils();
  static Utils *sharedInstance();

  void addNodeEntity(H3DNode node, Entity *entity);

  Entity *getEntityForNode(H3DNode node);
private:
  std::map<H3DNode, Entity*> nodeToEntity;
  static Utils *instance;
};

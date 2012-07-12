#include "Utils.h"

Utils *Utils::instance = NULL;

Utils::Utils()
{
  Utils::instance = this;
}

Utils *Utils::sharedInstance()
{
  if (Utils::instance == NULL) {
    new Utils();
  }
  return Utils::instance;
}

void Utils::addNodeEntity(H3DNode node, Entity *entity)
{
  nodeToEntity[node] = entity;
}

Entity *Utils::getEntityForNode(H3DNode node)
{
  return nodeToEntity[node];
}

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
  for (int i=0; 0 != h3dGetNodeChild(node, i); i++){
    addNodeEntity(h3dGetNodeChild(node, i), entity);
  }
}

Entity *Utils::getEntityForNode(H3DNode node)
{
  return nodeToEntity[node];
}

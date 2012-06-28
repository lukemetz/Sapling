#include "EntitySystem.h"

EntitySystem *Entity::entitySystem = 0;

Entity::Entity()
{
}

EntitySystem::EntitySystem()
{
	Entity::entitySystem = this;
}

void EntitySystem::removeAllComponents(Entity *e)
{
  std::map<TypeNameKey, Component*>::iterator it;

  for(it = e->mComponents.begin(); it != e->mComponents.end(); ++it) {
    mComponentStore.erase(it->first);
  }
}

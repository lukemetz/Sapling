#include "EntitySystem.h"

EntitySystem *Entity::entitySystem = 0;

Entity::Entity()
{
}

EntitySystem::EntitySystem()
{
	Entity::entitySystem = this;
}

EntitySystem::~EntitySystem()
{
  std::vector<System *>::iterator it;
  for(it=systems.begin(); it!=systems.end(); ++it) {
    delete (*it);
  }
  systems.clear();

  //TODO delete memory for components and entities
}

void EntitySystem::removeAllComponents(Entity *e)
{
  std::map<TypeNameKey, Component*>::iterator it;

  for(it = e->mComponents.begin(); it != e->mComponents.end(); ++it) {
    mComponentStore.erase(it->first);
  }
}

void EntitySystem::update(float dt)
{
  std::vector<System *>::iterator it;
  for(it=systems.begin(); it!=systems.end(); ++it) {
    (*it)->run(dt);
  }
}

System::~System()
{
}

#include "EntitySystem.h"

EntitySystem *Entity::entitySystem = 0;
EntitySystem *EntitySystem::instance = NULL;

Entity::Entity()
{
}

EntitySystem::EntitySystem()
{
	Entity::entitySystem = this;
  EntitySystem::instance = this;
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

EntitySystem *EntitySystem::sharedInstance()
{
  if (EntitySystem::instance == NULL) {
    new EntitySystem();
  }
  return EntitySystem::instance;
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

#include "EntitySystem.h"

EntitySystem *Entity::entitySystem = 0;
EntitySystem *EntitySystem::instance = NULL;

Entity::Entity()
{
}

Entity::~Entity()
{
  entitySystem->removeAllComponents(this);
}

std::string Component::Component::description()
{
  std::ostringstream stringStream;
  stringStream << "<Component ";
  stringStream << this;
  stringStream << ">";
  return stringStream.str();
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
  std::map<TypeNameKey, Component::Component*>::iterator it;

  for(it = e->mComponents.begin(); it != e->mComponents.end(); ++it) {

    std::multimap< TypeNameKey, Entity* >::iterator iter;
    //TODO fix me so I don't scale with number of components. Use better data structure
    auto iterPair = mComponentStore.equal_range(it->first);
    for(iter = iterPair.first; iter != iterPair.second; ++iter) {
      if (iter->second == e) {
        mComponentStore.erase(iter);
      }
    }
    e->mComponents.erase(it->first);
    printf("Clean 2 \n");
    delete it->second;
  }
}

void EntitySystem::update(float dt)
{
  std::vector<System *>::iterator it;
  for(it=systems.begin(); it!=systems.end(); ++it) {
    (*it)->run(dt);
  }
  for(it=systems.begin(); it!=systems.end(); ++it) {
    (*it)->preRun(dt);
  }
}

System::~System()
{
}

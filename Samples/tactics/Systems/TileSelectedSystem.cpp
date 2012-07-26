#include "TileSelectedSystem.h"
#include "Components/TileSelectedComponent.h"
#include <Components/components.h>

TileSelectedSystem::TileSelectedSystem()
{
  ensys = EntitySystem::sharedInstance();
}

void TileSelectedSystem::run(float dt)
{
  std::vector<Entity *> entities;
  ensys->getEntities<TileSelectedComponent>(entities);
  for (Entity *entity : entities) {
    TileSelectedComponent *tc = entity->getAs<TileSelectedComponent>();
    if(tc->prevSelected != tc->selected) {
      selectChanged(entity, tc->selected);
    }
    tc->prevSelected = tc->selected;
  }
}

void TileSelectedSystem::selectChanged(Entity *en, int select)
{
  TransformComponent * tc = en->getAs<TransformComponent>();
  if (select == 0) {
    tc->scale.x = 1;
    tc->scale.y = 1;
    tc->scale.z = 1;
  } else {
    tc->scale.x = .9;
    tc->scale.y = .9;
    tc->scale.z = .9;
  }
}


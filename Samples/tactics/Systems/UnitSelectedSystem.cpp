#include "UnitSelectedSystem.h"
#include "Components/UnitSelectedComponent.h"

void UnitSelectedSystem::preRun(float dt)
{
  auto entities = EntitySystem::sharedInstance()->getEntities<UnitSelectedComponent>();
  for (Entity * entity : entities) {
    auto component = entity->getAs<UnitSelectedComponent>();

    component->prevSelected = component->selected;
  }
}

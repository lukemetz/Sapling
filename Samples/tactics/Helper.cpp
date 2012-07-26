#include "Helper.h"
#include <Components/components.h>
#include "Components/PlayerStateComponent.h"
#include "Components/TileSelectedComponent.h"

Entity * Helper::getCamera()
{
  auto entities = EntitySystem::sharedInstance()->getEntities<CameraComponent>();
  if (entities.size() != 1) {
    printf("Wrong number of cameras, Currently have %d \n", static_cast<int>(entities.size()));
    throw;
  }
  return entities[0];
}

Entity * Helper::getPlayerState()
{
  auto entities = EntitySystem::sharedInstance()->getEntities<PlayerStateComponent>();
  if (entities.size() != 1) {
    printf("Wrong number of PlayerState, Currently have %d \n", static_cast<int>(entities.size()));
    throw;
  }
  return entities[0];
}

void Helper::deselectAllTiles()
{
  auto entities = EntitySystem::sharedInstance()->getEntities<TileSelectedComponent>();
  for (Entity *entity : entities) {
    entity->getAs<TileSelectedComponent>()->selected = false;
  }
}

#include "ComputerMovementSystem.h"
#include "Components/ComputerControlledComponent.h"
#include "Components/MovementComponent.h"

#include "Components/TileObjectComponent.h"
#include "Components/TileComponent.h"

void ComputerMovementSystem::run(float dt)
{
  auto entities = EntitySystem::sharedInstance()->getEntities<ComputerControlledComponent>();

  for (Entity *entity : entities) {
    //TODO Trigger only at the start of each turn

    auto movementComponent = entity->getAs<MovementComponent>();
    if (nullptr != movementComponent) {
      Entity *tile = entity->getAs<TileObjectComponent>()->tile;
      movementComponent->tiles.push_back(tile);
      movementComponent->tiles.push_back(tile->getAs<TileComponent>()->neighbors[0]);

    }
  }
}

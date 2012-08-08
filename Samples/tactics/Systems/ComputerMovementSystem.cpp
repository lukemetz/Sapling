#include "ComputerMovementSystem.h"
#include "Components/ComputerControlledComponent.h"
#include "Components/MovementComponent.h"

#include "Components/TileObjectComponent.h"
#include "Components/TileComponent.h"

#include "Helper.h"
#include "Components/PlayerStateComponent.h"

void ComputerMovementSystem::run(float dt)
{
  auto entities = EntitySystem::sharedInstance()->getEntities<ComputerControlledComponent>();

  for (Entity *entity : entities) {
    //TODO Trigger only at the start of each turn

    auto movementComponent = entity->getAs<MovementComponent>();
    if (nullptr != movementComponent) {
      auto computerControlled = entity->getAs<ComputerControlledComponent>();
      auto playerState = Helper::getPlayerState()->getAs<PlayerStateComponent>();
      if (playerState->turnStartTime > computerControlled->prevTurnStartTime) {
        computerControlled->prevTurnStartTime = playerState->turnStartTime;
        Entity *tile = entity->getAs<TileObjectComponent>()->tile;
        printf("Ai preforming movement \n");
        movementComponent->tiles.clear();
        movementComponent->startTime = playerState->turnStartTime;
        movementComponent->tiles.push_back(tile);
        movementComponent->tiles.push_back(tile->getAs<TileComponent>()->neighbors[0]);
      }
    }
  }
}

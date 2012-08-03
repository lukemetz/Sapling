#include "MovementSystem.h"

#include "Components/MovementComponent.h"
#include "Components/AnimationTimerComponent.h"
#include <Components/components.h>
#include "Components/TileObjectComponent.h"

MovementSystem::MovementSystem()
{
  ensys = EntitySystem::sharedInstance();
}

void MovementSystem::run(float dt)
{
  std::vector<Entity*> entities;
  ensys->getEntities<MovementComponent>(entities);
  for(Entity *entity : entities) {
    MovementComponent *mc = entity->getAs<MovementComponent>();
    AnimationTimerComponent *at = entity->getAs<AnimationTimerComponent>();
    TransformComponent *tc = entity->getAs<TransformComponent>();
    if (mc != NULL && at != NULL && tc != NULL) {
      if(at->time > mc->startTime) {
        float difference = at->time - mc->startTime;
        int currentTileIndex = static_cast<int>(difference * mc->speed);
        if (currentTileIndex < static_cast<int>(mc->tiles.size() - 1)) {
          mc->hasEndedRunning = false;
          Entity *t1 = mc->tiles[currentTileIndex];
          Entity *t2 = mc->tiles[currentTileIndex+1];
          TransformComponent *tc1 = t1->getAs<TransformComponent>();
          TransformComponent *tc2 = t2->getAs<TransformComponent>();
          float secondsBetween = difference - static_cast<int>(difference * mc->speed)/mc->speed;
          float percentBetween = secondsBetween*mc->speed;
          Vec3f newPos = tc1->pos*(1-percentBetween) + tc2->pos*percentBetween;
          tc->pos = newPos;
        } else if(mc->hasEndedRunning == false) {
          mc->hasEndedRunning = true;
          currentTileIndex = static_cast<int>(mc->tiles.size()-1);
          if (currentTileIndex > 0) {
            Entity * onTile = mc->tiles[currentTileIndex];
            entity->getAs<TileObjectComponent>()->tile = onTile;
          }
        }
      }
    }
  }
}

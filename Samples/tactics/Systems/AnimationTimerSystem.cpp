#include "AnimationTimerSystem.h"
#include "Components/AnimationTimerComponent.h"
#include "Components/PlayerStateComponent.h"

AnimationTimerSystem::AnimationTimerSystem()
{
  ensys = EntitySystem::sharedInstance();
}

void AnimationTimerSystem::run(float dt)
{
  std::vector<Entity*> entities;
  ensys->getEntities<AnimationTimerComponent>(entities);

  std::vector<Entity*> playerEntities;
  ensys->getEntities<PlayerStateComponent>(playerEntities);
  auto playerState = playerEntities[0]->getAs<PlayerStateComponent>();
  if (playerState->state != kPlayerAnimating)
  {
    return;
  }

  for(Entity *entity : entities) {
    entity->getAs<AnimationTimerComponent>()->time += dt;
  }
}


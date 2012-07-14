#include "AnimationTimerSystem.h"
#include "Components/AnimationTimerComponent.h"
AnimationTimerSystem::AnimationTimerSystem()
{
  ensys = EntitySystem::sharedInstance();
}

void AnimationTimerSystem::run(float dt)
{
  std::vector<Entity*> entities;
  ensys->getEntities<AnimationTimerComponent>(entities);

  for(Entity *entity : entities) {
    entity->getAs<AnimationTimerComponent>()->time += dt;
  }
}


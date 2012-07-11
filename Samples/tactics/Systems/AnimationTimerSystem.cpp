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

  std::vector<Entity*>::iterator it;
  for(it = entities.begin(); it != entities.end(); ++it) {
    Entity *en = *it;
    en->getAs<AnimationTimerComponent>()->time += dt;
  }
}


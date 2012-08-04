#include "AnimationTimerSystem.h"
#include "Components/AnimationTimerComponent.h"
#include "Components/PlayerStateComponent.h"
#include "Helper.h"

AnimationTimerSystem::AnimationTimerSystem()
{
  ensys = EntitySystem::sharedInstance();
}

void AnimationTimerSystem::run(float dt)
{
  auto entities = ensys->getEntities<AnimationTimerComponent>();

  auto playerState = Helper::getPlayerState()->getAs<PlayerStateComponent>();

  if (playerState->state != kPlayerAnimating)
  {
    return;
  }

  for(Entity *entity : entities) {
    entity->getAs<AnimationTimerComponent>()->time += dt;
    float time = entity->getAs<AnimationTimerComponent>()->time;
    if(playerState->state == kPlayerAnimating &&
        time - playerState->turnStartTime > playerState->timePerTurn ) {
      int turns = static_cast<int>(playerState->turnStartTime / playerState->timePerTurn);
      turns += 1;
      playerState->turnStartTime = turns * playerState->timePerTurn;
      playerState->state = kPlayerDeselected;
      printf("Turn animation ended on turn %d, with start %f \n", turns, playerState->turnStartTime);
    }
  }
}


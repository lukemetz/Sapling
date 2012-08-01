#include "PlayerStateComponent.h"

PlayerStateComponent::PlayerStateComponent()
{
  state = kPlayerDeselected;
  timePerTurn = 3;
  turnStartTime = 0;
}

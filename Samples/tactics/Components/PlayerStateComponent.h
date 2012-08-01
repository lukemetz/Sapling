#pragma once
#include <EntitySystem.h>

enum PlayerStates
{
  kPlayerDeselected,
  kPlayerSelected,
  kPlayerAnimating
};

struct PlayerStateComponent : public Component
{
  int state;
  float timePerTurn;
  float turnStartTime;
  PlayerStateComponent();
};

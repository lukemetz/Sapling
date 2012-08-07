#pragma once
#include <EntitySystem.h>

struct ComputerStateComponent : public Component
{
  float timePerTurn;
  float turnStartTime;
  float prevTurnStartTime;
  ComputerStateComponent();
};

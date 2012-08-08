#pragma once
#include <EntitySystem.h>

struct ComputerControlledComponent : public Component
{
  float prevTurnStartTime;
  ComputerControlledComponent();
};

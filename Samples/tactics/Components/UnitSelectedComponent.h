#pragma once
#include <EntitySystem.h>

struct UnitSelectedComponent : Component
{
  bool selected;
  bool usingAbility;
  UnitSelectedComponent();
};

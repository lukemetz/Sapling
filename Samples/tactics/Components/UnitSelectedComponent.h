#pragma once
#include <EntitySystem.h>

struct UnitSelectedComponent : Component
{
  bool selected;
  bool usingAbility;
  bool prevSelected;

  UnitSelectedComponent();
};

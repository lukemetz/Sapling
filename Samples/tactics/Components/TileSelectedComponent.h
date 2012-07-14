#pragma once

#include <stdio.h>
#include <EntitySystem.h>

struct TileSelectedComponent : public Component
{
  int selected;
  int prevSelected;
  TileSelectedComponent();
};

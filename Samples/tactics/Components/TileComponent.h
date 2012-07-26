#pragma once

#include <stdio.h>
#include <EntitySystem.h>

enum TileTypes
{
  kStone,
  kWoods,
  kWater
};

struct TileComponent : public Component
{
  std::vector<Entity *> neighbors;
  int type;
  TileComponent();
};

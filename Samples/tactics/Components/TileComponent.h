#include <stdio.h>
#include <EntitySystem.h>

struct TileComponent : public Component
{
  std::vector<Entity *> neighbors;
  TileComponent();
};

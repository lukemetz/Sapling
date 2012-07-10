#include <EntitySystem.h>
#include <stdlib.h>

struct MovementComponent : public Component
{
  float speed;
  float startTime;
  std::vector<Entity *> tiles;
  MovementComponent();
};

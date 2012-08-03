#include <EntitySystem.h>
#include <stdlib.h>

struct MovementComponent : public Component
{
  float speed;
  float startTime;
  bool hasEndedRunning;
  std::vector<Entity *> tiles;
  MovementComponent();
};

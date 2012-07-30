#include <EntitySystem.h>

struct MovementPath
{
  std::vector<Entity *> path;
  float time;
};

struct MovementSelectorComponent : public Component
{
  std::map<Entity *, MovementPath> possibleMoves;
};

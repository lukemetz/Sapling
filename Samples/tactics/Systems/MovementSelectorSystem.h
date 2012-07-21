#pragma once

#include <EntitySystem.h>

struct MovementPath;

class MovementSelectorSystem : public System
{
public:
  EntitySystem *ensys;
  MovementSelectorSystem();
  void run(float dt);
private:
  bool unitCanMove(Entity *entity);
  std::map<Entity *, MovementPath> getMovementLocationsAndPaths(Entity *entity);
  void selectPossibleLocations(Entity *entity);
};

struct MovementPath
{
  std::vector<Entity *> path;
  float time;
};

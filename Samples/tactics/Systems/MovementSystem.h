#include <EntitySystem.h>

class MovementSystem : public System
{
public:
  EntitySystem *ensys;
  MovementSystem(EntitySystem *entitySystem);
  void run(float dt);
};

#include <EntitySystem.h>

class MovementSystem : public System
{
public:
  EntitySystem *ensys;
  MovementSystem();
  void run(float dt);
};

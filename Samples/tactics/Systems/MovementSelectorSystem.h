#include <EntitySystem.h>

class MovementSelectorSystem : public System
{
public:
  EntitySystem *ensys;
  MovementSelectorSystem();
  void run(float dt);
};

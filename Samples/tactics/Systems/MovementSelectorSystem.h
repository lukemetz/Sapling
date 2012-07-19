#include <EntitySystem.h>

class MovementSelectorSystem : public System
{
public:
  EntitySystem *ensys;
  MovementSelectorSystem();
  void run(float dt);
private:
  bool unitCanMove(Entity *entity);
};

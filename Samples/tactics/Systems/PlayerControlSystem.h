#include <EntitySystem.h>
#include <Components/components.h>

#include "Components/PlayerStateComponent.h"

class PlayerControlSystem : public System
{
public:
  void run(float dt);
private:
  void mouseSelectObject(Entity *entity);
  void keyboardDeselect(Entity *entity);
  void selectUnit(Entity *current, Entity *selected);
  void deselectUnit(Entity *current);
};

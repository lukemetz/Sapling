#include <EntitySystem.h>

class AnimationTimerSystem : public System
{
  public:
    AnimationTimerSystem(EntitySystem* entitySystem);
    void run(float dt);
    EntitySystem *ensys;
};

#include <EntitySystem.h>

struct AnimationTimerComponent : public Component
{
  float time;
  bool isUpdating;
  AnimationTimerComponent();
};

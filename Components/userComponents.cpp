#include "userComponents.h"

InputMoverComponent::InputMoverComponent()
{
	speed = 2;
}

WobbleMoverComponent::WobbleMoverComponent()
{
  period = 1;
  displacement = Vec3f(0,0,20);
  offset = Vec3f(Math::Pi/2.0f,Math::Pi/2.0f,Math::Pi/2.0f);
  float time=0;
}

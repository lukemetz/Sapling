#include "userComponents.h"

using namespace Component;

InputMover::InputMover()
{
	speed = 2;
}

WobbleMover::WobbleMover()
{
  period = 1;
  displacement = Vec3f(0,0,20);
  offset = Vec3f(Math::Pi/2.0f,Math::Pi/2.0f,Math::Pi/2.0f);
}

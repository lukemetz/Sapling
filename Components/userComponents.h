#pragma once

#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>
#include "../EntitySystem.h"
#include "../utMath.h"
#include "../App.h"

struct InputMoverComponent : public Component
{
	float speed;
	InputMoverComponent();
};

struct WobbleMoverComponent : public Component
{
  float period;
  Vec3f displacement;
  Vec3f offset;
  float time;
  WobbleMoverComponent();
};

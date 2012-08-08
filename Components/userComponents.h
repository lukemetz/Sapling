#pragma once

#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>
#include "../EntitySystem.h"
#include "../utMath.h"
#include "../App.h"

namespace Component {
  struct InputMover : public Component
  {
    float speed;
    InputMover();
  };

  struct WobbleMover : public Component
  {
    float period;
    Vec3f displacement;
    Vec3f offset;
    float time;
    WobbleMover();
  };
};

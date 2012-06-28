#pragma once

#include "../EntitySystem.h"
#include "../Components/userComponents.h"
#include "../Components/components.h"
#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>

class InputMoverSystem : public System {
public:
	EntitySystem *ensys;
	InputMoverSystem(EntitySystem *en) {
		ensys = en;
	};
	void run(float dt);
};

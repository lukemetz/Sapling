#pragma once

#include "../EntitySystem.h"
#include "../Components/userComponents.h"
#include "../Components/components.h"
#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>

class InputHelperSystem : public System {
public:
	EntitySystem *ensys;
	InputHelperSystem() {
		ensys = EntitySystem::sharedInstance();
	};
	void run(float dt);
};

#pragma once

#include "../EntitySystem.h"
#include "../Components/userComponents.h"
#include "../Components/components.h"
#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>

class WobbleMoverSystem : public System {
public:
	EntitySystem *ensys;
	WobbleMoverSystem(EntitySystem *en) {
		ensys = en;
	};
	void run(float dt);
};

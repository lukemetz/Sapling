#pragma once

#include "../EntitySystem.h"
#include "../Components/components.h"

class InputSystem : public System
{
public:
	bool keys[320];
	bool prevKeys[320];
	int mouseX;
	int mouseY;
  EntitySystem *ensys;

  InputSystem(EntitySystem *en);
	void run(float dt);
};

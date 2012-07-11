#pragma once

#include "../EntitySystem.h"
#include "../Components/components.h"

class InputSystem : public System
{
public:
	bool keys[320];
	bool prevKeys[320];
  bool mouseButtons[8];
  bool prevMouseButtons[8];

  int mouseX;
	int mouseY;
  EntitySystem *ensys;

  InputSystem();
	void run(float dt);
};

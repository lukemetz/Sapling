#pragma once

#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>
#include "../EntitySystem.h"
#include "../Components/components.h"

using namespace Component;

class RenderSystem : public System
{
public:
	EntitySystem *ensys;
	RenderSystem();
	void run(float dt);
private:
  Camera* runCamera(float dt);
  void runMeshes(float dt);
  void runLights(float dt);
};

#pragma once

#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>
#include "../EntitySystem.h"
#include "../Components/components.h"

class RenderSystem : public System
{
public:
	EntitySystem *ensys;
	RenderSystem(EntitySystem *en);
	void run(float dt);
private:
  CameraComponent* runCamera(float dt);
  void runMeshes(float dt);
  void runLights(float dt);
};

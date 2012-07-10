#pragma once

#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>
#include "../EntitySystem.h"
#include "../utMath.h"
#include "../App.h"

struct CameraComponent : public Component
{
	CameraComponent();

	H3DNode node;
	H3DRes pipeline;
};

struct TransformComponent : public Component
{
	Vec3f pos;
	Vec3f scale;
	Vec3f rot;
	TransformComponent();
};

struct MeshComponent : public Component
{
  std::string path;
  MeshComponent();

  H3DNode node;
  H3DRes res;
  std::string oldPath;
  void loadResources();
};

struct InputComponent : public Component
{
	bool* keys;
	bool* prevKeys;
	float mouseX;
	float mouseY;
	float prevMouseX;
	float prevMouseY;
  bool* mouseButtons;
  bool* prevMouseButtons;
  InputComponent();
};

struct LightComponent : public Component
{
  Vec3f color;
  float radius;
  float fieldOfView;
  LightComponent();

  H3DNode node;
};

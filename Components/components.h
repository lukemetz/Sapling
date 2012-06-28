#pragma once

#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>
#include "../EntitySystem.h"
#include "../utMath.h"
#include "../App.h"

struct CameraComponent : public Component
{
	H3DNode node;
	H3DRes pipeline;
	CameraComponent();
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
	H3DRes res;
	H3DNode node;
	MeshComponent(std::string path);
};

struct InputComponent : public Component
{
	bool* keys;
	bool* prevKeys;
	float mouseX;
	float mouseY;
	float prevMouseX;
	float prevMouseY;
	InputComponent();
};

struct LightComponent : public Component
{
  H3DNode node;
  Vec3f color;
  float radius;
  float fieldOfView;
  LightComponent();
};

#include "components.h"

CameraComponent::CameraComponent()
{
	pipeline = h3dAddResource( H3DResTypes::Pipeline, "pipelines/hdr.pipeline.xml", 0 );
	std::string s = Application::appPath+"Content";
	h3dutLoadResourcesFromDisk(s.c_str());
	node = h3dAddCameraNode( H3DRootNode, "Camera", pipeline );
}

TransformComponent::TransformComponent()
{
	pos = Vec3f(0,0,0);
	scale = Vec3f(1,1,1);
	rot = Vec3f(0,0,0);
}

MeshComponent::MeshComponent()
{
  oldPath = "";
  res = 0;
  node = 0;
}

InputComponent::InputComponent()
{
	keys = 0;
	prevKeys = 0;
	mouseX = 0;
	mouseY = 0;
}

bool InputComponent::keyJustPressed(char key)
{
  return keys[static_cast<int>(key)] && !prevKeys[static_cast<int>(key)];
}

bool InputComponent::mouseJustPressed(int button)
{
  return mouseButtons[button] && !prevMouseButtons[button];
}

LightComponent::LightComponent()
{
  node = h3dAddLightNode(H3DRootNode, "", 0, "LIGHTING", "SHADOWMAP");
  color = Vec3f(1.f,1.f,1.f);
  radius = 100;
  fieldOfView = 360;
}

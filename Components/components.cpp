#include "components.h"

using namespace Component;

Camera::Camera()
{
	pipeline = h3dAddResource( H3DResTypes::Pipeline, "pipelines/hdr.pipeline.xml", 0 );
	std::string s = Application::appPath+"Content";
	h3dutLoadResourcesFromDisk(s.c_str());
	node = h3dAddCameraNode( H3DRootNode, "Camera", pipeline );
}

Transform::Transform()
{
	pos = Vec3f(0,0,0);
	scale = Vec3f(1,1,1);
	rot = Vec3f(0,0,0);
}

Mesh::Mesh()
{
  oldPath = "";
  res = 0;
  node = 0;
}

Input::Input()
{
	keys = 0;
	prevKeys = 0;
	mouseX = 0;
	mouseY = 0;
}

bool Input::keyJustPressed(char key)
{
  return keys[static_cast<int>(key)] && !prevKeys[static_cast<int>(key)];
}

bool Input::mouseJustPressed(int button)
{
  return mouseButtons[button] && !prevMouseButtons[button];
}

Light::Light()
{
  node = h3dAddLightNode(H3DRootNode, "", 0, "LIGHTING", "SHADOWMAP");
  color = Vec3f(1.f,1.f,1.f);
  radius = 100;
  fieldOfView = 360;
}

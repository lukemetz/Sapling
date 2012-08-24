#include "components.h"

using namespace Component;

Camera::Camera()
{
  debug = true;
  printf("start cam \n");
  pipeline = h3dAddResource( H3DResTypes::Pipeline, "pipelines/deferred.pipeline.xml", 0 );
	std::string s = Application::appPath+"Content";
  //Stats
  printf("%d node came \n", node);
	fontMatRes = h3dAddResource( H3DResTypes::Material, "overlays/font.material.xml", 0 );
	panelMatRes = h3dAddResource( H3DResTypes::Material, "overlays/panel.material.xml", 0 );

  h3dutLoadResourcesFromDisk(s.c_str());

  node = h3dAddCameraNode( H3DRootNode, "Camera", pipeline );
}

Transform::Transform()
{
	pos = Vec3f(0,0,0);
	scale = Vec3f(1,1,1);
	rot = Vec3f(0,0,0);
}

std::string Transform::description()
{
  std::ostringstream stringStream;
  stringStream << "<Transform pos:(";
  stringStream << pos.x;
  stringStream << ", ";
  stringStream << pos.y;
  stringStream << ", ";
  stringStream << pos.z;
  stringStream << ") scale:(";
  stringStream << scale.x;
  stringStream << ", ";
  stringStream << scale.y;
  stringStream << ", ";
  stringStream << scale.z;

  stringStream << ") rot:(";
  stringStream << rot.x;
  stringStream << ", ";
  stringStream << rot.y;
  stringStream << ", ";
  stringStream << rot.z;

  stringStream << ") >";
  return stringStream.str();
}

Mesh::Mesh()
{
  oldPath = "";
  res = 0;
  node = 0;
}

Mesh::~Mesh()
{
  if (node != 0)
  {
    h3dRemoveNode(node);
  }
}

std::string Mesh::description()
{
  std::ostringstream stringStream;
  stringStream << "<Component path=";
  stringStream << path;
  stringStream << " node=";
  stringStream << node;
  stringStream << ">";
  return stringStream.str();
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
  H3DRes lightMatRes = h3dAddResource (H3DResTypes::Material, "materials/light.material.xml", 0);
	std::string s = Application::appPath+"Content";
	h3dutLoadResourcesFromDisk(s.c_str());
  node = h3dAddLightNode(H3DRootNode, "light", lightMatRes, "LIGHTING", "SHADOWMAP");
  color = Vec3f(1.f,1.f,1.f);
  radius = 100;
  fieldOfView = 360;
}

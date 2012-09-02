#pragma once

#include <horde3d/Horde3D.h>
#include <horde3d/Horde3DUtils.h>
#include "../EntitySystem.h"
#include "../utMath.h"
#include "../App.h"

namespace Component
{

  struct Camera : public Component
  {
    Camera();
    bool debug;
    H3DNode node;
    H3DRes pipeline;
    //Stats
    H3DRes fontMatRes;
    H3DRes panelMatRes;
  };

  struct Transform : public Component
  {
    Vec3f pos;
    Vec3f scale;
    Vec3f rot;
    Transform();
    std::string description();
  };

  struct Mesh : public Component
  {
    std::string path;
    H3DNode node;
    H3DRes res;
    std::string oldPath;
    std::string description();
    void loadResources();
    Mesh();
    ~Mesh();
  };

  struct Input : public Component
  {
    bool* keys;
    bool* prevKeys;

    float mouseX;
    float mouseY;
    float prevMouseX;
    float prevMouseY;
    bool* mouseButtons;
    bool* prevMouseButtons;

    bool mouseJustPressed(int key);
    bool keyJustPressed(char key);
    Input();
  };

  struct Light : public Component
  {
    Vec3f color;
    float radius;
    float fieldOfView;
    Light();

    H3DNode node;
    std::string description();
  };

}

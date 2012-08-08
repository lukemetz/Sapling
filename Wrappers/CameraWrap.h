//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

using namespace Component;

class CameraWrap
{
  public:
    Camera* component;
    CameraWrap(Camera *com);

    void set(json_t *obj);
};
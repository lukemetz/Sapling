//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

class CameraComponentWrap
{
  public:
    CameraComponent* component;
    CameraComponentWrap(CameraComponent *com);

    void set(json_t *obj);
};
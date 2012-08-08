//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

using namespace Component;

class LightWrap
{
  public:
    Light* component;
    LightWrap(Light *com);

    void set(json_t *obj);
};
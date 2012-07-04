//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

class LightComponentWrap
{
  public:
    LightComponent* component;
    LightComponentWrap(LightComponent *com);

    void set(json_t *obj);
};
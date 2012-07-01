//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

class TransformComponentWrap
{
  public:
    TransformComponent* component;
    TransformComponentWrap(TransformComponent *com);

    void set(json_t *obj);
};
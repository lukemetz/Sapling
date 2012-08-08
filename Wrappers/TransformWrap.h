//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

using namespace Component;

class TransformWrap
{
  public:
    Transform* component;
    TransformWrap(Transform *com);

    void set(json_t *obj);
};
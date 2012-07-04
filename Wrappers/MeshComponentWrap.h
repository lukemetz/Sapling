//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

class MeshComponentWrap
{
  public:
    MeshComponent* component;
    MeshComponentWrap(MeshComponent *com);

    void set(json_t *obj);
};
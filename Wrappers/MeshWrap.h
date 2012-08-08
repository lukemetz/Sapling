//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

using namespace Component;

class MeshWrap
{
  public:
    Mesh* component;
    MeshWrap(Mesh *com);

    void set(json_t *obj);
};
//This file is auto generated
#pragma once
#include <jansson.h>
#include "../EntitySystem.h"

class WrapManager
{
  public:
    WrapManager();
    Entity* loadEntity(EntitySystem *ensys, json_t *obj);
};
//This file was automatically generated
#pragma once
#include "../Components/userComponents.h"
#include <jansson.h>

class WobbleMoverComponentWrap
{
  public:
    WobbleMoverComponent* component;
    WobbleMoverComponentWrap(WobbleMoverComponent *com);

    void set(json_t *obj);
};
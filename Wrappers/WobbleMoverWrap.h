//This file was automatically generated
#pragma once
#include "../Components/userComponents.h"
#include <jansson.h>

using namespace Component;

class WobbleMoverWrap
{
  public:
    WobbleMover* component;
    WobbleMoverWrap(WobbleMover *com);

    void set(json_t *obj);
};
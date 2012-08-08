//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

using namespace Component;

class InputWrap
{
  public:
    Input* component;
    InputWrap(Input *com);

    void set(json_t *obj);
};
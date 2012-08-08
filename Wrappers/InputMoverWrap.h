//This file was automatically generated
#pragma once
#include "../Components/userComponents.h"
#include <jansson.h>

using namespace Component;

class InputMoverWrap
{
  public:
    InputMover* component;
    InputMoverWrap(InputMover *com);

    void set(json_t *obj);
};
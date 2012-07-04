//This file was automatically generated
#pragma once
#include "../Components/userComponents.h"
#include <jansson.h>

class InputMoverComponentWrap
{
  public:
    InputMoverComponent* component;
    InputMoverComponentWrap(InputMoverComponent *com);

    void set(json_t *obj);
};
//This file was automatically generated
#pragma once
#include "../Components/components.h"
#include <jansson.h>

class InputComponentWrap
{
  public:
    InputComponent* component;
    InputComponentWrap(InputComponent *com);

    void set(json_t *obj);
};
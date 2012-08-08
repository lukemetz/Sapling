//This file was automatically generated
#include <string.h>
#include "InputMoverWrap.h"
InputMoverWrap::InputMoverWrap(InputMover *com)
{
  component=com;
}

void InputMoverWrap::set(json_t *obj)
{
  const char *key;
  json_t *value;
  json_object_foreach(obj, key, value) {
    if(strcmp(key,"speed")==0) {
      component->speed = json_number_value(value);
    }
  }
}
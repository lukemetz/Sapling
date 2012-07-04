//This file was automatically generated
#include <string.h>
#include "LightComponentWrap.h"
LightComponentWrap::LightComponentWrap(LightComponent *com)
{
  component=com;
}

void LightComponentWrap::set(json_t *obj)
{
  const char *key;
  json_t *value;
  json_object_foreach(obj, key, value) {
    if(strcmp(key,"color")==0) {
      json_t *v = json_array_get(value, 0);
      component->color.x = json_number_value(v);
      v = json_array_get(value, 1); 
      component->color.y = json_number_value(v);
      v = json_array_get(value, 2); 
      component->color.z = json_number_value(v);
    }
    if(strcmp(key,"fieldOfView")==0) {
      component->fieldOfView = json_number_value(value);
    }
    if(strcmp(key,"radius")==0) {
      component->radius = json_number_value(value);
    }
  }
}
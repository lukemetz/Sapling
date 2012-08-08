//This file was automatically generated
#include <string.h>
#include "WobbleMoverWrap.h"
WobbleMoverWrap::WobbleMoverWrap(WobbleMover *com)
{
  component=com;
}

void WobbleMoverWrap::set(json_t *obj)
{
  const char *key;
  json_t *value;
  json_object_foreach(obj, key, value) {
    if(strcmp(key,"time")==0) {
      component->time = json_number_value(value);
    }
    if(strcmp(key,"offset")==0) {
      json_t *v = json_array_get(value, 0);
      component->offset.x = json_number_value(v);
      v = json_array_get(value, 1); 
      component->offset.y = json_number_value(v);
      v = json_array_get(value, 2); 
      component->offset.z = json_number_value(v);
    }
    if(strcmp(key,"period")==0) {
      component->period = json_number_value(value);
    }
    if(strcmp(key,"displacement")==0) {
      json_t *v = json_array_get(value, 0);
      component->displacement.x = json_number_value(v);
      v = json_array_get(value, 1); 
      component->displacement.y = json_number_value(v);
      v = json_array_get(value, 2); 
      component->displacement.z = json_number_value(v);
    }
  }
}
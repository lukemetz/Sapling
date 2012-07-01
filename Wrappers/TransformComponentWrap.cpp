//This file was automatically generated
#include <string.h>
#include "TransformComponentWrap.h"
TransformComponentWrap::TransformComponentWrap(TransformComponent *com)
{
  component=com;
}

void TransformComponentWrap::set(json_t *obj)
{
  const char *key;
  json_t *value;
  json_object_foreach(obj, key, value) {
    if(strcmp(key,"scale")==0) {
      json_t *v = json_array_get(value, 0);
      component->scale.x = json_number_value(v);
      v = json_array_get(value, 1); 
      component->scale.y = json_number_value(v);
      v = json_array_get(value, 2); 
      component->scale.z = json_number_value(v);
    }
    if(strcmp(key,"rot")==0) {
      json_t *v = json_array_get(value, 0);
      component->rot.x = json_number_value(v);
      v = json_array_get(value, 1); 
      component->rot.y = json_number_value(v);
      v = json_array_get(value, 2); 
      component->rot.z = json_number_value(v);
    }
    if(strcmp(key,"pos")==0) {
      json_t *v = json_array_get(value, 0);
      component->pos.x = json_number_value(v);
      v = json_array_get(value, 1); 
      component->pos.y = json_number_value(v);
      v = json_array_get(value, 2); 
      component->pos.z = json_number_value(v);
    }
  }
}
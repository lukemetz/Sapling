//This file was automatically generated
#include <string.h>
#include "MeshComponentWrap.h"
MeshComponentWrap::MeshComponentWrap(MeshComponent *com)
{
  component=com;
}

void MeshComponentWrap::set(json_t *obj)
{
  const char *key;
  json_t *value;
  json_object_foreach(obj, key, value) {
    if(strcmp(key,"path")==0) {
      const char * val = json_string_value(value);
      component->path = std::string(val); 
    }
  }
}
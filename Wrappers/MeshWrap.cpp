//This file was automatically generated
#include <string.h>
#include "MeshWrap.h"
MeshWrap::MeshWrap(Mesh *com)
{
  component=com;
}

void MeshWrap::set(json_t *obj)
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
def wrapComponent(component):
  header = open(component["name"]+'Wrap.h', 'w')
  cpp = open(component["name"]+'Wrap.cpp', 'w')

  headerText = """//This file was automatically generated
#pragma once
#include "../Components/%(header)s"
#include <jansson.h>

class %(componentName)sWrap
{
  public:
    %(componentName)s* component;
    %(componentName)sWrap(%(componentName)s *com);

    void set(json_t *obj);
};"""
  header.write(headerText%\
      {"componentName" : component["name"], "header" : component["header"]});

  intro = """//This file was automatically generated
#include <string.h>
#include "%(componentName)sWrap.h"
%(componentName)sWrap::%(componentName)sWrap(%(componentName)s *com)
{
  component=com;
}

void %(componentName)sWrap::set(json_t *obj)
{
  const char *key;
  json_t *value;
  json_object_foreach(obj, key, value) {
"""
  vec3Property = """\
    if(strcmp(key,"%(param)s")==0) {
      json_t *v = json_array_get(value, 0);
      component->%(param)s.x = json_number_value(v);
      v = json_array_get(value, 1); 
      component->%(param)s.y = json_number_value(v);
      v = json_array_get(value, 2); 
      component->%(param)s.z = json_number_value(v);
    }
"""

  end = """  }
}"""
  cpp.write(intro%{"componentName" : component["name"]});
  par = component["params"]
  for name in par:
    if(par[name] == "vec3"):
      cpp.write(vec3Property%{"param": name});
  cpp.write(end);

component = {"name": "TransformComponent",\
    "params":{"pos" : "vec3", "scale" : "vec3", "rot" : "vec3"},\
    "header" : 'components.h'}
wrapComponent(component);

component = {"name": "CameraComponent", \
    "params":{}, "header": 'components.h'}

wrapComponent(component)

import os

def wrapManager(components, includes):
  pwd = os.path.dirname(__file__)
  if pwd == "":
    pwd = "."
  pwd += "/Wrappers"
  header = """//This file is auto generated
#pragma once
#include <jansson.h>
#include "../EntitySystem.h"

class WrapManager
{
  public:
    WrapManager();
    Entity* loadEntity(EntitySystem *ensys, json_t *obj);
};"""
  f = open(pwd+"/"+"WrapManager.h", "w");
  f.write(header);
  f.close();

  intro = """//This file is auto generated
#include "WrapManager.h"
#include <string.h>
"""
  file = open(pwd+"/"+"WrapManager.cpp",'w')
  file.write(intro);
  for include in includes:
    file.write("#include \"Components/%(include)s\"\n"%{"include":include})
 
  for component in components:
    file.write("#include \"Wrappers/%(com)sWrap.h\"\n"%{"com":component})
  
  next = """\
WrapManager::WrapManager()
{
}

Entity* WrapManager::loadEntity(EntitySystem *ensys, json_t *obj)
{
  const char *key;
  json_t *val;
  Entity *entity = new Entity();
  json_object_foreach(obj, key, val) {
"""
  file.write(next)
  
  preComponent = """\
    if (strcmp(key,"%(com)s") == 0) {
      %(com)s *c;
      c = ensys->createComponent<%(com)s>(entity);
      %(com)sWrap *cwrap = new %(com)sWrap(c);
      cwrap->set(val);
    }
"""
  for component in components:
    file.write(preComponent%{"com":component})

  end =""" 
  }
  return entity;
}"""

  file.write(end)
  file.close();

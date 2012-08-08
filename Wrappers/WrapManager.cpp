//This file is auto generated
#include "WrapManager.h"
#include <string.h>
#include "Components/userComponents.h"
#include "Components/components.h"
#include "Wrappers/WobbleMoverWrap.h"
#include "Wrappers/LightWrap.h"
#include "Wrappers/TransformWrap.h"
#include "Wrappers/MeshWrap.h"
#include "Wrappers/CameraWrap.h"
#include "Wrappers/InputWrap.h"
#include "Wrappers/InputMoverWrap.h"
WrapManager::WrapManager()
{
}

Entity* WrapManager::loadEntity(EntitySystem *ensys, json_t *obj)
{
  const char *key;
  json_t *val;
  Entity *entity = new Entity();
  json_object_foreach(obj, key, val) {
    if (strcmp(key,"WobbleMover") == 0) {
      WobbleMover *c;
      c = ensys->createComponent<WobbleMover>(entity);
      WobbleMoverWrap *cwrap = new WobbleMoverWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"Light") == 0) {
      Light *c;
      c = ensys->createComponent<Light>(entity);
      LightWrap *cwrap = new LightWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"Transform") == 0) {
      Transform *c;
      c = ensys->createComponent<Transform>(entity);
      TransformWrap *cwrap = new TransformWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"Mesh") == 0) {
      Mesh *c;
      c = ensys->createComponent<Mesh>(entity);
      MeshWrap *cwrap = new MeshWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"Camera") == 0) {
      Camera *c;
      c = ensys->createComponent<Camera>(entity);
      CameraWrap *cwrap = new CameraWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"Input") == 0) {
      Input *c;
      c = ensys->createComponent<Input>(entity);
      InputWrap *cwrap = new InputWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"InputMover") == 0) {
      InputMover *c;
      c = ensys->createComponent<InputMover>(entity);
      InputMoverWrap *cwrap = new InputMoverWrap(c);
      cwrap->set(val);
    }
 
  }
  return entity;
}
//This file is auto generated
#include "WrapManager.h"
#include <string.h>
#include "Components/components.h"
#include "Wrappers/CameraComponentWrap.h"
#include "Wrappers/TransformComponentWrap.h"
#include "Wrappers/InputComponentWrap.h"
WrapManager::WrapManager()
{
}

Entity* WrapManager::loadEntity(EntitySystem *ensys, json_t *obj)
{
  const char *key;
  json_t *val;
  Entity *entity = new Entity();
  json_object_foreach(obj, key, val) {
    if (strcmp(key,"CameraComponent") == 0) {
      CameraComponent *c;
      c = ensys->createComponent<CameraComponent>(entity);
      CameraComponentWrap *cwrap = new CameraComponentWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"TransformComponent") == 0) {
      TransformComponent *c;
      c = ensys->createComponent<TransformComponent>(entity);
      TransformComponentWrap *cwrap = new TransformComponentWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"InputComponent") == 0) {
      InputComponent *c;
      c = ensys->createComponent<InputComponent>(entity);
      InputComponentWrap *cwrap = new InputComponentWrap(c);
      cwrap->set(val);
    }
 
  }
  return entity;
}
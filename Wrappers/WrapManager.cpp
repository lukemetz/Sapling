//This file is auto generated
#include "WrapManager.h"
#include <string.h>
#include "Components/components.h"
#include "Components/userComponents.h"
#include "Wrappers/CameraComponentWrap.h"
#include "Wrappers/TransformComponentWrap.h"
#include "Wrappers/LightComponentWrap.h"
#include "Wrappers/WobbleMoverComponentWrap.h"
#include "Wrappers/InputComponentWrap.h"
#include "Wrappers/MeshComponentWrap.h"
#include "Wrappers/InputMoverComponentWrap.h"
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
    if (strcmp(key,"LightComponent") == 0) {
      LightComponent *c;
      c = ensys->createComponent<LightComponent>(entity);
      LightComponentWrap *cwrap = new LightComponentWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"WobbleMoverComponent") == 0) {
      WobbleMoverComponent *c;
      c = ensys->createComponent<WobbleMoverComponent>(entity);
      WobbleMoverComponentWrap *cwrap = new WobbleMoverComponentWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"InputComponent") == 0) {
      InputComponent *c;
      c = ensys->createComponent<InputComponent>(entity);
      InputComponentWrap *cwrap = new InputComponentWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"MeshComponent") == 0) {
      MeshComponent *c;
      c = ensys->createComponent<MeshComponent>(entity);
      MeshComponentWrap *cwrap = new MeshComponentWrap(c);
      cwrap->set(val);
    }
    if (strcmp(key,"InputMoverComponent") == 0) {
      InputMoverComponent *c;
      c = ensys->createComponent<InputMoverComponent>(entity);
      InputMoverComponentWrap *cwrap = new InputMoverComponentWrap(c);
      cwrap->set(val);
    }
 
  }
  return entity;
}
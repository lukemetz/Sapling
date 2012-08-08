//With help from:
//http://unseen-academy.de/snippet_component_system.html

#pragma once

#include <stdio.h>
#include "map"
#include "vector"
#include <typeinfo>

class EntitySystem;

typedef const char * TypeNameKey;

namespace Component
{
  struct Component
  {
  };
};

struct Entity
{
   static EntitySystem *entitySystem;
   Entity();
   template<typename Type> Type *getAs();

   std::map<TypeNameKey, Component::Component*> mComponents;
};

class System
{
public:
  virtual void run(float dt)
  {
  };
  virtual void preRun(float dt)
  {
  };
  virtual ~System();
};

class EntitySystem
{
public:
   EntitySystem();
   ~EntitySystem();

   static EntitySystem *sharedInstance();

   template<typename T> T *getComponent(Entity *e)
   {
      return (T*)e->mComponents[typeid(T).name()];
   }

   template<typename T> void getEntities(std::vector<Entity*> &result)
   {
      std::multimap< TypeNameKey, Entity* >::iterator iter;

      auto iterPair = mComponentStore.equal_range(typeid(T).name());
      for(iter = iterPair.first; iter != iterPair.second; ++iter) {
         result.push_back(iter->second);
      }
   }

   template<typename T> std::vector<Entity *> getEntities()
   {
      std::vector<Entity *> entities;
      getEntities<T>(entities);
      return entities;
   }

   template<typename T> T* createComponent(Entity* e)
   {
      T *t = new T();
      addComponent(e, t);
      return t;
   }

   template<typename T> void addComponent(Entity *e, T* comp)
   {
      mComponentStore.insert(std::pair<TypeNameKey, Entity*>(typeid(T).name(), e));
      e->mComponents.insert(std::pair<TypeNameKey, Component::Component*>(typeid(T).name(), comp));
   }

   template<typename T> void removeComponent(Entity *e)
   {
      mComponentStore.erase(typeid(T).name());
      e->mComponents.erase(typeid(T).name());
   }

   void removeAllComponents(Entity *e);

   template<typename T> T* addSystem()
   {
      T *system = new T();
      systems.push_back(system);
      return system;
   }

   void update(float dt);

protected:
   std::multimap<TypeNameKey, Entity*> mComponentStore;
   std::vector<System *> systems;
   static EntitySystem *instance;
};

template<typename Type> Type *Entity::getAs()
{
   return entitySystem->getComponent<Type>(this);
}

//With help from:
//http://unseen-academy.de/snippet_component_system.html

#pragma once

#include <stdio.h>
#include "map"
#include "vector"
#include <typeinfo>

class EntitySystem;

typedef const char * TypeNameKey;

struct Component
{
};

struct Entity
{
   static EntitySystem *entitySystem;
   Entity();
   template<typename Type> Type *getAs();

   std::map<TypeNameKey, Component*> mComponents;
};

class EntitySystem
{
public:
   EntitySystem();

   template<typename T> T *getComponent(Entity *e)
   {
      return (T*)e->mComponents[typeid(T).name()];
   }

   template<typename T> void getEntities(std::vector<Entity*> &result)
   {
      std::pair< std::multimap< TypeNameKey, Entity* >::iterator,
         std::multimap< TypeNameKey, Entity* >::iterator> iterPair;

      std::multimap< TypeNameKey, Entity* >::iterator iter;

      iterPair = mComponentStore.equal_range(typeid(T).name());
      for(iter = iterPair.first; iter != iterPair.second; ++iter) {
         result.push_back(iter->second);
      }
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
      e->mComponents.insert(std::pair<TypeNameKey, Component*>(typeid(T).name(), comp));
   }

   template<typename T> void removeComponent(Entity *e)
   {
      mComponentStore.erase(typeid(T).name());
      e->mComponents.erase(typeid(T).name());
   }

   void removeAllComponents(Entity *e);

protected:
   std::multimap<TypeNameKey, Entity*> mComponentStore;

};

template<typename Type> Type *Entity::getAs()
{
   return entitySystem->getComponent<Type>(this);
}

class System
{
public:
  virtual void run(float dt)
  {
  };
};

#include <gtest/gtest.h>
#include "Components/components.h"
#include "EntitySystem.h"

class EntitySystemTest: public ::testing::Test
{
  protected:
    EntitySystem *entitySystem;

    virtual void SetUp()
    {
      entitySystem = new EntitySystem();
    }

    virtual void TearDown()
    {
      delete entitySystem;
    }
};

TEST_F(EntitySystemTest, createComponent)
{
  Entity* e1 = new Entity();
  entitySystem->createComponent<TransformComponent>(e1);

  std::vector<Entity*> entities;
  entitySystem->getEntities<TransformComponent>(entities);

  EXPECT_EQ(1, entities.size());

  Entity* e2 = new Entity();
  entitySystem->createComponent<TransformComponent>(e2);

  entities.clear();
  entitySystem->getEntities<TransformComponent>(entities);

  EXPECT_EQ(2,entities.size());

  delete e1;
  delete e2;
}

TEST_F(EntitySystemTest, addComponent_getEntities)
{
  TransformComponent *tc = new TransformComponent();
  Entity* entity = new Entity();
  entitySystem->addComponent<TransformComponent>(entity,tc);

  std::vector<Entity*> entities;
  entitySystem->getEntities<TransformComponent>(entities);
  EXPECT_EQ(1, entities.size());

  EXPECT_EQ(entities[0]->getAs<TransformComponent>(), tc);

  entities.clear();
  entitySystem->getEntities<CameraComponent>(entities);
  EXPECT_EQ(0, entities.size());

  delete tc;
  delete entity;
}

TEST_F(EntitySystemTest, getAs)
{
  TransformComponent *tc = new TransformComponent();
  Entity* entity = new Entity();
  entitySystem->addComponent<TransformComponent>(entity,tc);

  std::vector<Entity*> entities;
  entitySystem->getEntities<TransformComponent>(entities);

  EXPECT_EQ(entities[0]->getAs<TransformComponent>(), tc);

  delete tc;
  delete entity;
}

TEST_F(EntitySystemTest, removeComponent)
{
  TransformComponent *tc = new TransformComponent();
  Entity* entity = new Entity();
  entitySystem->addComponent<TransformComponent>(entity,tc);
  entitySystem->removeComponent<TransformComponent>(entity);

  std::vector<Entity*> entities;
  entitySystem->getEntities<TransformComponent>(entities);

  EXPECT_EQ(entities.size(), 0);

  entitySystem->removeComponent<CameraComponent>(entity);
  entities.clear();
  entitySystem->getEntities<CameraComponent>(entities);

  EXPECT_EQ(entities.size(),0);

  delete tc;
  delete entity;
}


TEST_F(EntitySystemTest, removeAllComponents)
{
  TransformComponent *tc = new TransformComponent();
  Entity* entity = new Entity();

  entitySystem->addComponent<TransformComponent>(entity,tc);
  entitySystem->removeAllComponents(entity);

  std::vector<Entity*> entities;
  entitySystem->getEntities<TransformComponent>(entities);
  EXPECT_EQ(0, entities.size());

  delete tc;
  delete entity;
}

TEST_F(EntitySystemTest, singleton)
{
  EntitySystem *ensys = EntitySystem::sharedInstance();
  EXPECT_EQ(ensys, entitySystem);
}

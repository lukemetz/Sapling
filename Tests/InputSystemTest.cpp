#include <gtest/gtest.h>
#include "EntitySystem.h"
#include "Components/components.h"
#include "Systems/InputSystem.h"

class InputSystemTest: public ::testing::Test
{
  protected:
    EntitySystem *entitySystem;
    std::vector<Entity*> entities;
    InputSystem *inputSystem;

    virtual void SetUp()
    {
      entitySystem = new EntitySystem();
      for(int i=0; i < 10; i++) {
        Entity *entity = new Entity();
        entities.push_back(entity);
        entitySystem->createComponent<InputComponent>(entity);
      }
      inputSystem = new InputSystem();
    }

    virtual void TearDown()
    {
      delete entitySystem;
      delete inputSystem;
    }
};

TEST_F(InputSystemTest, DoesSetKeyboardOnComponents)
{
  inputSystem->run(0.1f);
  inputSystem->keys['e'] = true;
  inputSystem->keys['w'] = true;
  inputSystem->mouseX = 123.1f;
  inputSystem->mouseY = 1.0f;
  inputSystem->run(0.1f);

  std::vector<Entity *> en;
  entitySystem->getEntities<InputComponent>(en);

  for(int i=0; i < 5; i++) {
    EXPECT_EQ(en[i]->getAs<InputComponent>()->keys['w'], false);
    EXPECT_EQ(en[i]->getAs<InputComponent>()->keys['e'], false);
    EXPECT_EQ(en[i]->getAs<InputComponent>()->keys['j'], false);

    EXPECT_EQ(en[i]->getAs<InputComponent>()->prevKeys['w'], true);
    EXPECT_EQ(en[i]->getAs<InputComponent>()->prevKeys['e'], true);
    EXPECT_EQ(en[i]->getAs<InputComponent>()->prevKeys['j'], false);
  }
}

TEST_F(InputSystemTest, DoesSetMouseOnComponents)
{
  inputSystem->run(0.1f);
  inputSystem->mouseX = 123.1f;
  inputSystem->mouseY = 1.0f;

  std::vector<Entity *> en;
  entitySystem->getEntities<InputComponent>(en);

  for(int i=0; i < 4; i++) {
    en[i]->getAs<InputComponent>()->mouseX = 123.1f;
    en[i]->getAs<InputComponent>()->mouseY = 1.0f;
  }

  inputSystem->run(0.1f);

  for(int i=0; i < 4; i++) {
    EXPECT_FLOAT_EQ(en[i]->getAs<InputComponent>()->prevMouseX, 123.1f);
    EXPECT_FLOAT_EQ(en[i]->getAs<InputComponent>()->prevMouseY, 1.0f);
  }
}

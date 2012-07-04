#include <gtest/gtest.h>
#include <jansson.h>
#include "Wrappers/WrapManager.h"
#include "Components/components.h"
#include "Components/userComponents.h"
#include "EntitySystem.h"


#include "App.h"

TEST(WrapManagerTest, loadEntity)
{
  std::string jsonStream = "{\"TransformComponent\"\
                            :{\"pos\":[1.0,2.0,3], \
                              \"scale\":[3,2,1], \
                              \"rot\":[1.12,2.11,3.04]},\
                            \"InputComponent\":{}, \
                              \"MeshComponent\" : {\
                              \"path\" : \"someMesh.xml\"}, \
                              \"WobbleMoverComponent\" : {\
                              \"period\":4.123}}";

  json_error_t *error = NULL;
  WrapManager *wrapManager = new WrapManager();
  EntitySystem *ensys = new EntitySystem();

  Entity *en = wrapManager->loadEntity(ensys, json_loads(jsonStream.c_str(), 0, error));

  TransformComponent *tc = en->getAs<TransformComponent>();
  EXPECT_FLOAT_EQ(tc->pos.x, 1);
  EXPECT_FLOAT_EQ(tc->pos.y, 2);
  EXPECT_FLOAT_EQ(tc->pos.z, 3);

  EXPECT_FLOAT_EQ(tc->scale.x, 3);
  EXPECT_FLOAT_EQ(tc->scale.y, 2);
  EXPECT_FLOAT_EQ(tc->scale.z, 1);

  EXPECT_FLOAT_EQ(tc->rot.x, 1.12);
  EXPECT_FLOAT_EQ(tc->rot.y, 2.11);
  EXPECT_FLOAT_EQ(tc->rot.z, 3.04);

  std::vector<Entity*> entities;
  ensys->getEntities<InputComponent>(entities);
  EXPECT_EQ(entities.size(), 1);

  MeshComponent *mc = en->getAs<MeshComponent>();
  EXPECT_STREQ("someMesh.xml", mc->path.c_str());

  WobbleMoverComponent *c = en->getAs<WobbleMoverComponent>();

  EXPECT_FLOAT_EQ(c->period, 4.123);
}

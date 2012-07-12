#include <gtest/gtest.h>
#include "Utils.h"
#include "EntitySystem.h"

TEST(Utils, nodeToEntity)
{
  Utils *ut = new Utils();
  Entity *en = new Entity;
  Entity *en2 = new Entity;

  ut->addNodeEntity(12, en);
  ut->addNodeEntity(11, en);
  ut->addNodeEntity(9, en2);

  EXPECT_EQ(en, ut->getEntityForNode(12));
  EXPECT_EQ(en, ut->getEntityForNode(11));
  EXPECT_EQ(en2, ut->getEntityForNode(9));
}

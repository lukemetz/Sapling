#include <gtest/gtest.h>
#include <jansson.h>
#include "Wrappers/TransformComponentWrap.h"

TEST(TransformComponentWrap, set)
{
  std::string jsonStream = "{\"pos\":[1.0,2.0,3], \"scale\":[3,2,1], \"rot\":[1.12,2.11,3.04]}";
  TransformComponent *tc = new TransformComponent();
  TransformComponentWrap *tcwrap = new TransformComponentWrap(tc);
  json_error_t *error = NULL;
  tcwrap->set(json_loads(jsonStream.c_str(), 0, error));
  EXPECT_FLOAT_EQ(tc->pos.x, 1);
  EXPECT_FLOAT_EQ(tc->pos.y, 2);
  EXPECT_FLOAT_EQ(tc->pos.z, 3);

  EXPECT_FLOAT_EQ(tc->scale.x, 3);
  EXPECT_FLOAT_EQ(tc->scale.y, 2);
  EXPECT_FLOAT_EQ(tc->scale.z, 1);

  EXPECT_FLOAT_EQ(tc->rot.x, 1.12);
  EXPECT_FLOAT_EQ(tc->rot.y, 2.11);
  EXPECT_FLOAT_EQ(tc->rot.z, 3.04);
}

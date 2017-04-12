#include "slices.h"
#include "gtest/gtest.h"

TEST(SlicesTest, describe) {
  const Slices s0{{0,8},{2,122,2}};
  EXPECT_EQ("0:8,2:122:2", s0.describe());

  const Slices s1;
}


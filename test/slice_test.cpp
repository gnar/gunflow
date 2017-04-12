#include "slice.h"
#include "gtest/gtest.h"

TEST(SliceTest, values) {
  const Slice slice(3, 14, 2);

  EXPECT_EQ(3, slice.x0);
  EXPECT_EQ(14, slice.x1);
  EXPECT_EQ(2, slice.step);
}

TEST(SliceTest, describe) {
  EXPECT_EQ("0:10", Slice(0, 10).describe());
  EXPECT_EQ("3:14:2", Slice(3, 14, 2).describe());
}


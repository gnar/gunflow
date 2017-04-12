#include "strides.h"
#include "shape.h"

#include "gtest/gtest.h"

#include <sstream>

class StridesTest : public ::testing::Test {
protected:
  const Strides strides0;
  const Strides strides1{1, 20, 400};
};

TEST_F(StridesTest, has_correct_values_0) {
  ASSERT_EQ(0, strides0.ndim);
}

TEST_F(StridesTest, has_correct_values_1) {
  ASSERT_EQ(3, strides1.ndim);
  ASSERT_EQ(1, strides1.vec[0]);
  ASSERT_EQ(20, strides1.vec[1]);
  ASSERT_EQ(400, strides1.vec[2]);
}

TEST_F(StridesTest, describe) {
  ASSERT_EQ("(1, 20, 400)", strides1.describe());
}

TEST_F(StridesTest, row_major) {
  const auto strides = Strides::row_major({10, 20, 30}, sizeof(float));

  ASSERT_EQ(3, strides.ndim);
  EXPECT_EQ(2400, strides.vec[0]);
  EXPECT_EQ(120, strides.vec[1]);
  EXPECT_EQ(4, strides.vec[2]);
}

TEST_F(StridesTest, column_major) {
  const auto strides = Strides::column_major({10, 20, 30}, sizeof(float));

  ASSERT_EQ(3, strides.ndim);
  EXPECT_EQ(4, strides.vec[0]);
  EXPECT_EQ(40, strides.vec[1]);
  EXPECT_EQ(800, strides.vec[2]);
}

TEST_F(StridesTest, linidx_zero) {
  EXPECT_EQ(0, strides1.linidx({}));
  EXPECT_EQ(0, strides1.linidx({0}));
  EXPECT_EQ(0, strides1.linidx({0, 0}));
  EXPECT_EQ(0, strides1.linidx({0, 0, 0}));

  EXPECT_EQ(0, strides1.linidx(0));
  EXPECT_EQ(0, strides1.linidx(0, 0));
  EXPECT_EQ(0, strides1.linidx(0, 0, 0));
}

TEST_F(StridesTest, linidx) {
  EXPECT_EQ(1, strides1.linidx(1, 0, 0));
  EXPECT_EQ(20, strides1.linidx(0, 1, 0));
  EXPECT_EQ(400, strides1.linidx(0, 0, 1));

  EXPECT_EQ(421, strides1.linidx(1, 1, 1));
}


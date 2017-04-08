#include "shape.h"
#include "gtest/gtest.h"

class ShapeTest : public ::testing::Test {
protected:
  const Shape shape0;
  const Shape shape1{10, 20, 30};
};

TEST_F(ShapeTest, has_correct_values_0) {
  ASSERT_EQ(0, shape0.ndim);
  ASSERT_EQ(1, shape0.nelem);
}

TEST_F(ShapeTest, has_correct_values_1) {
  ASSERT_EQ(3, shape1.ndim);
  ASSERT_EQ(6000, shape1.nelem);
  ASSERT_EQ(10, shape1.vec[0]);
  ASSERT_EQ(20, shape1.vec[1]);
  ASSERT_EQ(30, shape1.vec[2]);
}

TEST_F(ShapeTest, describe) {
  std::stringstream ss;
  shape1.describe(ss);
  ASSERT_EQ("(10, 20, 30)", ss.str());
}


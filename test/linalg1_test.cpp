#include "linalg1.h"
#include "gtest/gtest.h"

TEST(Linalg1Test, fill) {
  NDArray a({10, 10, 10});

  fill(a, 42.0);

  for (int i=0; i<10; ++i)
  for (int j=0; j<10; ++j)
  for (int k=0; k<10; ++k) {
    ASSERT_EQ(42.0, a.at<float>(i, j, k));
  }
}

TEST(Linalg1Test, scale) {
  NDArray a({10, 10, 10});

  for (int i=0; i<10; ++i)
  for (int j=0; j<10; ++j)
  for (int k=0; k<10; ++k) {
    a.at<float>(i, j, k) = 2*i + 5*j + 7*k;
  }

  scale(a, 10);

  for (int i=0; i<10; ++i)
  for (int j=0; j<10; ++j)
  for (int k=0; k<10; ++k) {
    ASSERT_EQ(20*i + 50*j + 70*k, a.at<float>(i, j, k));
  }
}

TEST(Linalg1Test, normal) {
  NDArray a({100, 100, 100});

  normal(a, 7.0, 3.0);

  float sum1 = 0.0, sum2 = 0.0;

  for (int i=0; i<100; ++i)
  for (int j=0; j<100; ++j)
  for (int k=0; k<100; ++k) {
    float tmp = a.at<float>(i, j, k);
    sum1 += tmp;
    sum2 += tmp * tmp;
  }

  float mean = sum1 / a.shape.nelem;
  float var = (sum2 / a.shape.nelem) - (mean * mean);

  EXPECT_NEAR(7.0, mean, 0.01) << "mean is: " << mean;
  EXPECT_NEAR(9.0, var, 0.01) << "var is: " << var;
}


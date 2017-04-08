#include "buffer.h"
#include "gtest/gtest.h"

class BufferTest : public ::testing::Test {
protected:
  Buffer buf0 = Buffer(4096);
};

TEST_F(BufferTest, size) {
  ASSERT_EQ(4096, buf0.size);
}

TEST_F(BufferTest, data) {
  ASSERT_TRUE(buf0.data != nullptr);
}

TEST_F(BufferTest, at) {
  buf0.at<float>(0) = 42.0;
  ASSERT_EQ(42.0, buf0.at<float>(0));
}

TEST_F(BufferTest, copy) {
  for (int i=0; i<4096; ++i) {
    buf0.at<char>(i) = i % 32;
  }
  
  auto buf1 = buf0;
  ASSERT_EQ(buf1.size, 4096);
  ASSERT_NE(buf1.data, buf0.data);
  
  for (int i=0; i<4096; ++i) {
    ASSERT_EQ(i % 32, buf0.at<char>(i));
  }
}

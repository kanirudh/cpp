#include "gtest/gtest.h"
#include "data_structures/circular_array.h"

TEST(CircularArray, basic) {
  CircularArray<int, 10> arr;
  for (int i = 0; i < 10; i++) {
    arr.Push(i);
  }

  EXPECT_TRUE(arr.Full());

  for (int i = 0; i < 10; i++) {
    auto front = arr.Pop();
    EXPECT_TRUE(front);
    EXPECT_EQ(front.value(), i);
  }

  EXPECT_FALSE(arr.Pop());
}

TEST(CircularArray, overflow) {
  CircularArray<int, 10> arr;
  for (int i = 0; i < 11; i++) {
    arr.Push(i);
  }
  for (int i = 0; i < 10; i++) {
    auto front = arr.Pop();
    EXPECT_TRUE(front);
    EXPECT_EQ(front.value(), i);
  }
}

//
// Created by Anirudh Agrawal on 5/24/26.
//

#include "data_structures/CustomUniquePtr.h"
#include "gtest/gtest.h"

struct LifeCycleCounter {
  LifeCycleCounter(int& counter) : counter_(counter) {
    ++counter_;
  }

  ~LifeCycleCounter() {
    --counter_;
  }

  int& counter_;
};
TEST(CustomUniquePtr, Basic) {
  int count = 0;
  {
    CustomUniquePtr<LifeCycleCounter> ptr1(new LifeCycleCounter(count));
    EXPECT_EQ(count, 1);
  }

  EXPECT_EQ(count, 0);
}


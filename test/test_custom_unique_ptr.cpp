//
// Created by Anirudh Agrawal on 5/24/26.
//

#include "data_structures/CustomUniquePtr.h"
#include "gtest/gtest.h"

struct LifeCycleCounter {
  LifeCycleCounter(int& counter) : counter_(counter) { ++counter_; }

  ~LifeCycleCounter() { --counter_; }

  int& counter_;
};

TEST(CustomUniquePtr, Basic) {
  int count = 0;
  {
    CustomUniquePtr<LifeCycleCounter> ptr1(new LifeCycleCounter(count));
    EXPECT_EQ(count, 1);
    EXPECT_TRUE(ptr1);

    EXPECT_EQ(ptr1->counter_, 1);
  }

  EXPECT_EQ(count, 0);
}

TEST(CustomUniquePtr, MoveAssignment) {
  int count = 0;
  {
    CustomUniquePtr<LifeCycleCounter> ptr1(new LifeCycleCounter(count));
    CustomUniquePtr<LifeCycleCounter> ptr2(new LifeCycleCounter(count));
    EXPECT_EQ(count, 2);
    ptr1 = std::move(ptr2);
    EXPECT_EQ(count, 1);
  }
  EXPECT_EQ(count, 0);
}

TEST(CustomUniquePtr, Reset) {
  int count = 0;
  CustomUniquePtr<LifeCycleCounter> ptr1(new LifeCycleCounter(count));
  EXPECT_EQ(count, 1);
  ptr1.reset();
  EXPECT_EQ(count, 0);
}

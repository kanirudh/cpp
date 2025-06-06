#include <thread>

#include "concurrency/concurrent_stack.h"
#include "gtest/gtest.h"

TEST(ConcurrentStack, basic) {
  ConcurrentStack<int> stack;
  static constexpr int kNum = 100;
  std::jthread t1([&stack]() {
    for (int i = 1; i <= kNum; ++i) {
      stack.Push(i);
    }
  });
  std::jthread t2([&stack]() {
    for (int i = 1; i <= kNum; ++i) {
      stack.Push(i);
    }
  });

  int popped = 0;
  int sum = 0;
  while (popped < 2 * kNum) {
    auto v = stack.Pop();
    while (not v) {
      v = stack.Pop();
      std::this_thread::yield();
    }
    sum += v.value();
    ++popped;
  }
  EXPECT_EQ(sum, kNum * (kNum + 1));
}

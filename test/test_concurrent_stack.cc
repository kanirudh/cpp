#include <atomic>
#include <thread>
#include <vector>

#include "concurrency/concurrent_stack.h"
#include "gtest/gtest.h"

TEST(ConcurrentStack, basic) {
  ConcurrentStack<int> stack;
  static constexpr int kNum = 100;
  std::thread t1([&stack]() {
    for (int i = 1; i <= kNum; ++i) {
      stack.Push(i);
    }
  });
  std::thread t2([&stack]() {
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
  t1.join();
  t2.join();
}

// Verify LIFO ordering is correct on a single thread.
TEST(ConcurrentStack, SingleThread_LIFOOrder) {
  ConcurrentStack<int> stack;
  stack.Push(1);
  stack.Push(2);
  stack.Push(3);

  EXPECT_EQ(stack.Pop().value(), 3);
  EXPECT_EQ(stack.Pop().value(), 2);
  EXPECT_EQ(stack.Pop().value(), 1);
}

// Verify Pop() on an empty stack returns an error and empty() is consistent.
TEST(ConcurrentStack, EmptyBehavior) {
  ConcurrentStack<int> stack;

  EXPECT_TRUE(stack.empty());

  auto result = stack.Pop();
  EXPECT_FALSE(result.has_value());
  EXPECT_EQ(result.error(), "Empty");

  stack.Push(42);
  EXPECT_FALSE(stack.empty());

  [[maybe_unused]] auto _ = stack.Pop();
  EXPECT_TRUE(stack.empty());
}

// Push N unique elements on one thread then have multiple consumers race to
// pop them. Every element must be popped exactly once — no duplicates, no
// lost elements.
TEST(ConcurrentStack, NoDuplicatePops_SingleProducer_MultiConsumer) {
  static constexpr int kNum = 10'000;
  static constexpr int kConsumers = 4;

  ConcurrentStack<int> stack;
  for (int i = 0; i < kNum; ++i) stack.Push(i);

  std::vector<std::atomic<int>> pop_count(kNum);
  std::atomic<int> total_popped{0};

  auto consumer = [&]() {
    while (total_popped.load(std::memory_order_relaxed) < kNum) {
      auto v = stack.Pop();
      if (v) {
        pop_count[v.value()].fetch_add(1, std::memory_order_relaxed);
        total_popped.fetch_add(1, std::memory_order_relaxed);
      }
    }
  };

  std::vector<std::thread> threads;
  for (int i = 0; i < kConsumers; ++i) threads.emplace_back(consumer);
  for (auto& t : threads) t.join();

  for (int i = 0; i < kNum; ++i) {
    EXPECT_EQ(pop_count[i].load(), 1)
        << "element " << i << " was popped " << pop_count[i] << " time(s)";
  }
}

// Multiple producers push unique (thread_id, seq) pairs encoded as a single
// int. Multiple consumers pop concurrently. Verify every pushed element is
// popped exactly once — catches both lost elements and double-pops.
TEST(ConcurrentStack, NoLostElements_MultiProducer_MultiConsumer) {
  static constexpr int kProducers = 4;
  static constexpr int kConsumers = 4;
  static constexpr int kPerProducer = 2'500;
  static constexpr int kTotal = kProducers * kPerProducer;

  ConcurrentStack<int> stack;
  std::vector<std::atomic<int>> pop_count(kTotal);

  std::atomic<bool> producers_done{false};

  // Consumers: drain until producers are done and stack is empty.
  std::vector<std::thread> consumers;
  for (int i = 0; i < kConsumers; ++i) {
    consumers.emplace_back([&]() {
      while (!producers_done.load(std::memory_order_acquire) || !stack.empty()) {
        auto v = stack.Pop();
        if (v) {
          pop_count[v.value()].fetch_add(1, std::memory_order_relaxed);
        }
      }
    });
  }

  // Producers: each pushes a unique range of ids.
  std::vector<std::thread> producers;
  for (int t = 0; t < kProducers; ++t) {
    producers.emplace_back([&, t]() {
      int base = t * kPerProducer;
      for (int i = 0; i < kPerProducer; ++i) stack.Push(base + i);
    });
  }

  for (auto& t : producers) t.join();
  producers_done.store(true, std::memory_order_release);
  for (auto& t : consumers) t.join();

  for (int i = 0; i < kTotal; ++i) {
    EXPECT_EQ(pop_count[i].load(), 1)
        << "element " << i << " was popped " << pop_count[i] << " time(s)";
  }
}

// Verify that every popped node is deleted. Uses a Tracked type whose
// destructor decrements a counter — if nodes are leaked the counter stays > 0.
TEST(ConcurrentStack, PopDeletesNode) {
  static std::atomic<int> live_count{0};
  struct Tracked {
    Tracked()                          { live_count.fetch_add(1, std::memory_order_relaxed); }
    Tracked(const Tracked&)            { live_count.fetch_add(1, std::memory_order_relaxed); }
    Tracked(Tracked&&) noexcept        { live_count.fetch_add(1, std::memory_order_relaxed); }
    ~Tracked()                         { live_count.fetch_sub(1, std::memory_order_relaxed); }
  };

  live_count.store(0);
  {
    ConcurrentStack<Tracked> stack;
    stack.Push(Tracked{});
    stack.Push(Tracked{});
    stack.Push(Tracked{});
    EXPECT_EQ(live_count.load(), 3);  // one Tracked alive per node

    [[maybe_unused]] auto a = stack.Pop();
    [[maybe_unused]] auto b = stack.Pop();
    [[maybe_unused]] auto c = stack.Pop();
    EXPECT_EQ(live_count.load(), 3);  // returned values still alive
  }
  EXPECT_EQ(live_count.load(), 0);    // everything destroyed — no leaks
}

// High-contention stress test: every thread interleaves pushes and pops.
// After all threads finish, drain the stack. Total pops must equal total
// pushes — no element is created or destroyed spuriously.
TEST(ConcurrentStack, StressTest_MixedOps) {
  static constexpr int kThreads = 8;
  static constexpr int kOpsPerThread = 10'000;

  ConcurrentStack<int> stack;
  std::atomic<int> push_count{0};
  std::atomic<int> pop_count{0};

  std::vector<std::jthread> threads;
  threads.reserve(kThreads);
  for (int t = 0; t < kThreads; ++t) {
    threads.emplace_back([&, t]() {
      for (int i = 0; i < kOpsPerThread; ++i) {
        if (i % 2 == 0) {
          stack.Push(i);
          push_count.fetch_add(1, std::memory_order_relaxed);
        } else {
          if (stack.Pop().has_value()) {
            pop_count.fetch_add(1, std::memory_order_relaxed);
          }
        }
      }
    });
  }

  for (auto& t : threads) t.join();

  // Drain any remaining elements.
  while (!stack.empty()) {
    if (stack.Pop().has_value()) {
      pop_count.fetch_add(1, std::memory_order_relaxed);
    }
  }

  EXPECT_EQ(push_count.load(), pop_count.load());
}

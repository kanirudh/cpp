// This is a well stuided problem with some common considerations
// 1. ABA problem
// 2.

#pragma once

template <typename T>
class ThreadSafeLinkedList {

  struct Node {


  };

public:
  ThreadSafeLinkedList() = default;
  ~ThreadSafeLinkedList() = default;

  void Push(T value) {}

  T Pop() {}

  bool Empty() const noexcept {}

  size_t Size() const noexcept { return size_; }


private:
  size_t size_;
};

//
// Created by Anirudh Agrawal on 2/14/26.
//

#ifndef POOLALLOCATOR_H
#define POOLALLOCATOR_H

#include <array>
#include <new>
#include <algorithm>
#include <cstddef>

namespace allocator {
template <typename T>
class PoolAllocator {
public:
  using value_type = T;

  void init() noexcept {
    auto* current = storage_.data();
    free_ = reinterpret_cast<FreeNode*>(current);
    for (size_t i = 0; i < kNum - 1; ++i, current += kBlockSize) {
      reinterpret_cast<FreeNode*>(current)->next = reinterpret_cast<FreeNode*>(current + kBlockSize);
    }
    reinterpret_cast<FreeNode*>(current)->next = nullptr;
    available_ = kNum;
  }

  PoolAllocator() noexcept {
    init();
  }

  template <typename U>
  PoolAllocator(const PoolAllocator<U>&) noexcept {
    init();
  }

  PoolAllocator(const PoolAllocator&) noexcept {
    init();
  }

  PoolAllocator& operator=(const PoolAllocator&) noexcept {
    return *this;
  }

  PoolAllocator(PoolAllocator&&) noexcept {
    init();
  }

  PoolAllocator& operator=(PoolAllocator&&) noexcept {
    return *this;
  }

  value_type* allocate(size_t n) {
    if (n != 1 || free_ == nullptr) throw std::bad_alloc();
    T* ret = reinterpret_cast<T*>(free_);
    free_ = free_->next;
    --available_;
    return ret;
  }

  void deallocate(T* p, size_t n) {
    if (n != 1) throw std::bad_alloc();
    auto* next = reinterpret_cast<FreeNode*>(p);
    next->next = free_;
    free_ = next;
    ++available_;
  }

  template <typename U>
  bool operator==(const PoolAllocator<U>&) const noexcept {
    return true;
  }

  template <typename U>
  bool operator!=(const PoolAllocator<U>&) const noexcept {
    return false;
  }

private:
  struct FreeNode {
    FreeNode* next;
  };
  static_assert(sizeof(FreeNode) == 8);
  static_assert(sizeof(FreeNode*) == 8);
  static constexpr size_t kNum = 128;
  static constexpr size_t kBlockSize = std::max(sizeof(T), sizeof(FreeNode*));
  std::array<std::byte, kNum * kBlockSize> storage_;
  FreeNode* free_ = nullptr;
  int available_ = kNum;
};

}
#endif //POOLALLOCATOR_H

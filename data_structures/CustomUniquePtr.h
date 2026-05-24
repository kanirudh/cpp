//
// Created by Anirudh Agrawal on 5/24/26.
//

#include <utility>

#ifndef CPP_CUSTOMUNIQUEPTR_H
#define CPP_CUSTOMUNIQUEPTR_H

template <typename T>
class CustomUniquePtr {
public:
  CustomUniquePtr(T* ptr) : ptr_(ptr) {}
  ~CustomUniquePtr() {
    release();
  }

  CustomUniquePtr(const CustomUniquePtr<T>& other) = delete;
  CustomUniquePtr& operator=(const CustomUniquePtr<T>& other) = delete;

  CustomUniquePtr(CustomUniquePtr<T>&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {}
  CustomUniquePtr& operator=(CustomUniquePtr<T>&& other) noexcept {
    ptr_ = std::exchange(other.ptr_, nullptr);
    return *this;
  }

  explicit operator T&() noexcept { return *ptr_; }

  void reset() noexcept {
    ptr_ = nullptr;
  }
private:

  void release() {
    delete ptr_;
    ptr_ = nullptr;
  }

private:
  T* ptr_ = nullptr;
};

#endif  // CPP_CUSTOMUNIQUEPTR_H

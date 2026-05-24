//
// Created by Anirudh Agrawal on 5/24/26.
//
#ifndef CPP_CUSTOMUNIQUEPTR_H
#define CPP_CUSTOMUNIQUEPTR_H

#include <utility>

template <typename T>
class CustomUniquePtr {
public:
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;
  using const_reference = const T&;

  CustomUniquePtr(pointer ptr) : ptr_(ptr) {}
  ~CustomUniquePtr() {
    delete ptr_;
  }

  CustomUniquePtr(const CustomUniquePtr<T>& other) = delete;
  CustomUniquePtr& operator=(const CustomUniquePtr<T>& other) = delete;

  CustomUniquePtr(CustomUniquePtr<T>&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {}
  CustomUniquePtr& operator=(CustomUniquePtr<T>&& other) noexcept {
    if (this != &other) {
      delete ptr_;
      ptr_ = std::exchange(other.ptr_, nullptr);
    }
    return *this;
  }

  explicit operator bool() const noexcept {return ptr_ != nullptr;}

  reference operator*() noexcept {return *ptr_;}
  const_reference operator*() const noexcept {return *ptr_;}
  pointer operator->() noexcept {return ptr_;}
  const_pointer operator->() const noexcept {return ptr_;}

  void reset(pointer value = pointer()) noexcept {
    if (ptr_ != nullptr) {
      delete ptr_;
    }
    ptr_ = value;
  }

  void release() {
    ptr_ = nullptr;
  }

private:

  pointer ptr_ = nullptr;
};

#endif  // CPP_CUSTOMUNIQUEPTR_H

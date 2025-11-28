//
// Created by Anirudh Agrawal on 11/28/25.
//

#ifndef OPTIONAL_H
#define OPTIONAL_H

#include <concepts>
#include <type_traits>

// A bit-packed optional struct
// What are other concerns which I need to address here ?
// TODO(anirudh): Aliasing ?

template <typename T, T SENTINEL>
requires std::integral<std::underlying_type_t<T>>
struct Optional {
  Optional() : value_(SENTINEL) {}
  explicit Optional(T value) : value_(value) {}

  Optional(Optional const& other) : value_(other.value_) {}
  Optional& operator=(T value) { value_ = value; return *this; }

  Optional(Optional&& other) noexcept : value_(std::exchange(other.value_, SENTINEL)){}

  T operator*() const noexcept { assert(value_ != SENTINEL); return value_;}

  bool has_value() const noexcept { return value_ != SENTINEL; }

  T value() noexcept { return value_; }

private:
  static constexpr size_t SIZE = 3;
  T value_ : SIZE = SENTINEL;
};

#endif //OPTIONAL_H

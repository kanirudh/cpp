#include <cassert>
#include <utility>

/*
 * In the test example one can see benefit of this approach in template
 * metaprogramming where the vvariable can be abstracted away
 */
template <typename T, bool Enabled>
struct Conditional {
  T value_;

  // If the underlying type supports the following operations then we do as
  // well.
  Conditional() = default;
  Conditional(Conditional const& other) = default;
  Conditional(Conditional&& other) = default;

  Conditional(T&& _value) : value_(std::forward<T>(_value)) {}

  T& value() { return value_; }
};

template <typename T>
struct __attribute__((packed)) Conditional<T, false> {
  Conditional() = default;
  Conditional([[maybe_unused]] T&& _value) {}
  Conditional(Conditional const& other) = default;
  Conditional(Conditional&& other) = default;
};

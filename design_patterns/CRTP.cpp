/* This is a way to achieve static polymorphism where the interface defined by
 * the Base Class cannot be modified, while the implemenation is hidden in
 * Derived class
 *
 *
 * What are the downsides/limitations to CRTP ?
 *
 * 1. This can only be exposed a header library because each while buildling a
 * translation unit the implementation has to be known to the Base class.
 */

#include <iostream>

template <typename Derived>
class Base {
 public:
  void Name() {
    std::cout << __PRETTY_FUNCTION__ << " calling the base function"
              << std::endl;
    impl().NameImpl();
  }

 private:
  Derived& impl() { return static_cast<Derived&>(*this); }
  friend Derived;
};

class Derived : public Base<Derived> {
  using Parent = Base<Derived>;

 private:
  void NameImpl() { std::cout << __PRETTY_FUNCTION__ << std::endl; }
  friend Parent;
};

int main() {
  Derived x;
  x.Name();
  return 0;
}

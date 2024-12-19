#include <iostream>
#include <typeinfo>

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

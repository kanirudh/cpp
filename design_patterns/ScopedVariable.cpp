/*
 * There are instances in a progream when one wants to set a value of variable
 * which serves as a configuration while running the test. This is only usefull
 * for global variables.
 */

#include <iostream>

template <typename T>
class ScopedSetter {
 public:
  ScopedSetter(T& variable, T newvalue) : v{variable}, old_value{variable} {
    variable = newvalue;
  }
  ~ScopedSetter() {
    std::cout << "Reversing the new setting" << std::endl;
    v = old_value;
  }

 private:
  T& v;

  T old_value;
};

#define NEWVALUE_STR "_newvalue"

#define SCOPED_SETTER(VARIABLE, NEW_VALUE) \
  auto newvalue_##VARIABLE = ScopedSetter(VARIABLE, NEW_VALUE);

int main() {
  int x = 42;
  {
    SCOPED_SETTER(x, 56);
    std::cout << x << std::endl;
  }
  std::cout << x << std::endl;
  return 0;
}

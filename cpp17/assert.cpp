#include <string>
#include <type_traits>

int main() {
  // string a = "Hello";
  static_assert(std::is_arithmetic_v<std::string>);

  return 0;
}

#include <iostream>
#include <string>
#include <variant>

template <typename T>
void visitor1(T const& mv) {
  std::visit([](auto&& arg) { std::cout << arg << std::endl; }, mv);
}

int main() {
  std::variant<int, std::string> mv;
  mv = "Anirudh";
  visitor1(mv);
  mv = 45;
  visitor1(mv);
  return 0;
}

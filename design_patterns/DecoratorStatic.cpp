
#include <algorithm>
#include <iostream>
#include <string>

class Person {
 public:
  Person(std::string name, std::string address, int age)
      : name_{std::move(name)}, address_{std::move(address)}, age_{age} {}

  std::string Stringify() const {
    std::string result;
    result += "Name: " + name_ + " ";
    result += "Address: " + address_ + " ";
    result += "Age: " + std::to_string(age_);
    return result;
  }

 private:
  std::string name_;
  std::string address_;
  int age_;
};

template <typename Base>
class LowerCaseDecorator {
 public:
  LowerCaseDecorator(Base const& base) : base_{base} {}

  std::string Stringify() const {
    auto result = base_.Stringify();
    std::transform(result.begin(), result.end(), result.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return result;
  }

 private:
  Base const& base_;
};

template <typename T>
void LowerCasePrint(T const& obj) {
  LowerCaseDecorator<T> temp(obj);
  std::cout << temp.Stringify() << std::endl;
}

int main() {
  auto commander = new Person{"Anirudh", "Varanasi", 24};
  LowerCasePrint(*commander);

  return 0;
}

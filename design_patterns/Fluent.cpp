/*
 * Fluent Interface Idiom
 * This is more of an interface rather than a design pattern. The main idea is
 * to achieve method chaining.
 */

#include <iostream>

class Boat {
 public:
  Boat& setFuel(int const f) {
    fuel = f;
    return *this;
  }

  Boat& setName(std::string const& name) {
    this->name = name;
    return *this;
  }

  void display() const {
    std::cout << this->name << " has " << this->fuel << " litres of fuel\n";
  }

 private:
  int fuel;
  std::string name;
};

int main() {
  Boat b;
  b.setFuel(10).setName("DarkMoon").display();

  return 0;
}

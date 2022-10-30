#include <iostream>
#include <optional>
#include <vector>

#include "constructor_printing_class.h"

std::optional<ConstructorPrintingClass> getObject(int x) {
  if (x == 0) return std::nullopt;

  // This one results in first a Default Construction followed by a move into
  // std::optional container
  // return ConstructorPrintingClass();

  // This leads to only a single construction because of mandatory Copy Ellision
  // in C++17;
  return std::optional<ConstructorPrintingClass>{std::in_place};
}

int main() {
  auto obj = getObject(1);
  return 0;
}

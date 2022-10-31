#include <cassert>
#include <cstddef>
#include <iostream>
#include <string>
#include <tuple>
#include <type_traits>

#include "reflection.h"

// TODO(anirudh) reorganise this into multiple files.

template <int... I>
struct Vector;

template <typename input, typename output = Vector<>>
struct uniq;

template <int First, int... Remaining, int... Result>
struct uniq<Vector<First, First, Remaining...>, Vector<Result...>> {
  using type =
      typename uniq<Vector<First, Remaining...>, Vector<Result...>>::type;
};

template <int First, int... Remaining, int... Result>
struct uniq<Vector<First, Remaining...>, Vector<Result...>> {
  using type =
      typename uniq<Vector<Remaining...>, Vector<Result..., First>>::type;
};

template <typename Output>
struct uniq<Vector<>, Output> {
  using type = Output;
};

class Company {
 public:
  Company(int num_emplyees, std::string name, int year)
      : number_of_employees_{num_emplyees},
        name_{std::move(name)},
        year_of_inception_{year} {}

  auto reflect() const {
    return std::tie(number_of_employees_, name_, year_of_inception_);
  }

 private:
  int number_of_employees_;

  std::string name_;

  int year_of_inception_;
};

class Employee {
 public:
  Employee(int64_t jd, std::string name, int salary)
      : joining_date_{jd}, name_{std::move(name)}, salary_{salary} {}
  bool operator==(Employee const& other) {
    std::cout << "Normal comparator chosen";
    return joining_date_ == other.joining_date_;
  }

 private:
  int64_t joining_date_;
  std::string name_;
  int salary_;
};

int main() {
  static_assert(
      std::is_same_v<Vector<1, 2, 3>, uniq<Vector<1, 1, 2, 2, 3>>::type>);

  auto meta = Company{100, "Meta", 2006};
  auto google = Company{101, "Google", 1998};

  assert(meta < google);

  auto e1 = Employee(13456, "rockstar", 5000);
  auto e2 = Employee(13456, "superstar", 15000);
  assert(e1 == e2);
  return 0;
}

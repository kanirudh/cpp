//
// Created by Anirudh Agrawal on 6/5/26.
//

#include <iostream>
#include "gtest/gtest.h"

template <typename T>
void f(int T::* ) {
  std::cout << "Is a class" << std::endl;
}

template <typename T>
void f(...) {
  std::cout << "Not a class" << std::endl;
}

template <typename T>
struct is_class {
  template <typename C> static char test(int C::*);
  template <typename C> static int test(...);

  static constexpr bool value = sizeof(test<T>(0)) == sizeof(char);
};

TEST(Sfinae, IsClass) {
  struct A {};
  class B {};
  f<A>(0);
  f<B>(0);
  f<int>(A{});
  static_assert(is_class<A>::value, "");
  static_assert(is_class<B>::value, "");
  static_assert(!is_class<int>::value, "");
}
namespace memfn {
struct yes { char c; };
struct no { char c; yes c1; };

template <typename T> yes test(decltype(&T::sort));
template <typename T> no test(decltype(&T::sort));
}

TEST(Sfinae, member_function) {

}

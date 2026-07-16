//
// Created by Anirudh Agrawal on 6/5/26.
//

#include <iostream>
#include <algorithm>
#include <type_traits>
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

template <typename T> std::true_type test(decltype(&T::Sort));
template <typename T> std::false_type test(...);


template <typename T, typename Specialized>
struct FastSort {
  static void Sort(T& t) {
    std::ranges::sort(t.begin(), t.end());
  }
};

template <typename T>
struct FastSort<T, std::true_type> {
  static void Sort(T& t) {
    t.Sort();
  }
};

template <typename T>
void fast_sort_dispatch(T& t) {
  FastSort<T, decltype(test<T>(nullptr))>::Sort(t);
}

}

TEST(Sfinae, member_function) {
  class Anirudh {
    public:
      void Sort() {
        std::cout << "Called" << std::endl;
      }
  };

  Anirudh anirudh;
  memfn::fast_sort_dispatch(anirudh);

}

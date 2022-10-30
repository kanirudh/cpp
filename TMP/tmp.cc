#include <cassert>
#include <iostream>
#include <type_traits>

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

int main() {
  static_assert(
      std::is_same_v<Vector<1, 2, 3>, uniq<Vector<1, 1, 2, 2, 3>>::type>);
  return 0;
}
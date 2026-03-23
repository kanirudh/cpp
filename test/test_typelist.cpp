#include "gtest/gtest.h"
#include <type_traits>

template <typename ... Ts>
struct TypeList;

template <typename ... Ts>
struct Head;

template <typename T, typename ... Ts>
struct Head<TypeList<T, Ts...>> {
  using type = T;
};

template <typename ... Ts>
using Head_t = typename Head<Ts...>::type;


template <typename ... Ts>
struct Tail;

template <typename T>
struct Tail<TypeList<T>> {
  using type = T;
};

template <typename T, typename ... Ts>
struct Tail<TypeList<T, Ts...>> {
  using type = typename Tail<TypeList<Ts...>>::type;
};

template <typename ... Ts>
struct Size {};

template <typename ... Ts>
struct Size<TypeList<Ts...>> {
  constexpr static size_t value = sizeof...(Ts);
};

TEST(TypeList, Head) {
  using List = TypeList<int, float, double>;
  {
    constexpr bool result = std::is_same_v<int, Head_t<List>>;
    EXPECT_TRUE(result);
  }
  {
    constexpr bool result = std::is_same_v<char, Head_t<List>>;
    EXPECT_FALSE(result);
  }
}

TEST(TypeList, Tail) {
  using List = TypeList<int, float, double>;
  {
    constexpr bool result = std::is_same_v<double, Tail<List>::type>;
    EXPECT_TRUE(result);
  }
  {
    constexpr bool result = std::is_same_v<char, Tail<List>::type>;
    EXPECT_FALSE(result);
  }
}

TEST(TypeList, Size) {
  {
    using List = TypeList<int, float, double>;
    constexpr auto result = Size<List>::value;
    EXPECT_EQ(result, 3);
  }
  {
    using List = TypeList<>;
    constexpr auto result = Size<List>::value;
    EXPECT_EQ(result, 0);
  }
}
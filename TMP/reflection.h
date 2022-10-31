#include <experimental/type_traits>

template <typename T>
using has_reflect_member = decltype(&T::reflect);

template <typename T>
constexpr bool is_reflectable_v =
    std::experimental::is_detected<has_reflect_member, T>::value;

template <typename T, bool IsReflectable = is_reflectable_v<T>>
auto operator==(T const& a, T const& b)
    -> std::enable_if_t<IsReflectable, bool> {
  return a.reflect() == b.reflect();
}

template <typename T, bool IsReflectable = is_reflectable_v<T>>
auto operator<(T const& a, T const& b)
    -> std::enable_if_t<IsReflectable, bool> {
  return a.reflect() < b.reflect();
}

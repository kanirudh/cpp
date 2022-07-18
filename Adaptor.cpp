/*
 * This plans to add a wrapper of sort of an existing implementaiton
 * to provide some additional features and cleaner api
 *
 * https://sourcemaking.com/design_patterns/adapter
 */

#include <array>
#include <cassert>
#include <iostream>
#include <vector>

/*
 * This class a mixture of array and vector
 * to gain the advantage of stack for small sizes
 */
template <typename T>
class VariableArray {
  static const constexpr size_t MAX_ARRAY_LENGTH = 10;

  std::array<T, MAX_ARRAY_LENGTH> m_array;
  std::vector<T> m_vector;
  size_t m_size{0};

 public:
  VariableArray() = default;

  VariableArray(size_t size) {
    if (size > MAX_ARRAY_LENGTH) {
      m_vector.reserve(size - MAX_ARRAY_LENGTH);
    }
  }

  void push_back(T const& data) {
    if (m_size < MAX_ARRAY_LENGTH) {
      m_array[m_size] = data;
    } else {
      m_vector.push_back(data);
    }
    m_size++;
  }

  // Returns reference to the last element.
  T& back() {
    if (m_size <= MAX_ARRAY_LENGTH) {
      return m_array[m_size - 1];
    }
    return m_vector.back();
  }

  void pop_back() {
    if (m_size == 0) return;

    if (m_size > MAX_ARRAY_LENGTH) {
      m_vector.pop_back();
    }
    // TODO: In the array case should we call the destuctor
    m_size--;
  }
};

int main() {
  VariableArray<int> va;

  for (int i = 0; i < 25; i++) {
    va.push_back(i);
    assert(va.back() == i);
  }

  for (int i = 0; i < 25; i++) {
    std::cout << va.back() << std::endl;
    va.pop_back();
  }
  return 0;
}

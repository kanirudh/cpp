#include <atomic>
#include <expected>
#include <string>

// TODO(anirudh): Support an allocator.
template <typename T>
class ConcurrentStack {
  struct Node {
    T value;
    Node *next;
  };

 public:
  template <typename... U>
    requires std::is_constructible_v<T, U...>
  void Push(U &&...value) {
    auto *n = new Node(std::forward<U>(value)...);
    auto *h = head.load(std::memory_order_acquire);
    n->next = h;
    while (not head.compare_exchange_strong(h, n, std::memory_order_release,
                                            std::memory_order_acquire)) {
      n->next = h;
    }
  }

  std::expected<T, std::string> Pop() {
    auto *h = head.load(std::memory_order_acquire);
    while (h != nullptr and not head.compare_exchange_strong(
                                h, h->next, std::memory_order_acquire,
                                std::memory_order_relaxed)) {
    }
    if (h == nullptr) {
      return std::unexpected("Empty");
    }
    return h->value;
  }

  [[gnu::always_inline]] bool empty() const {
    return head.load(std::memory_order_acquire) == nullptr;
  }

 private:
  std::atomic<Node *> head = nullptr;
};

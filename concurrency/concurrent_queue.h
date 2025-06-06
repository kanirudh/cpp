/*
 * Describes a concurrent linked list FIFO queue.
 */
#include <atomic>

template <typename T>
class ConcurrentQueue {
  struct Node {
    T value;
    Node* next = nullptr;
  };

 public:
  void push(T&& value) {
    auto* n = new Node(std::forward<T>(value));
    auto i = index.load(std::memory_order_relaxed);
    auto ni = i;
    ni.tail = n;
    n->next = i.head;
    while (head.compare_exchange_strong(h, n)) {
      n->next = h;
    }
  }

  bool pop_front(T& val) {
    auto* h = head.load(std::memory_order_relaxed);
    while (h != nullptr and not head.compare_exchange_strong(h, h->next)) {
    }
    if (h == nullptr) {
      return false;
    }
    val = std::move(h->val);
    return true;
  }

  bool empty() const { return head.load() == nullptr; }

 private:
  struct Index {
    Node* head;
    Node* tail;
  };
  std::atomic<Index> index;
  static_assert(decltype(index)::is_always_lock_free);
  // std::atomic<Node*> head;
  // std::atomic<Node*> tail;
};

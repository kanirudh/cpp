#include <mutex>
#include <optional>

template <typename T>
class tll {
  struct Node {
    T value;
    Node* next = nullptr;
    Node* prev = nullptr;
  };

 public:
  using iterator = T*;

  bool empty() const {
    std::scoped_lock lock(mtx);
    return head == nullptr;
  }
  size_t size() const {
    std::scoped_lock lock(mtx);
    return head == nullptr;
  }

  T& emplace_back(T&& value) {
    Node* n = new Node(std::forward<T>(value));
    std::scoped_lock lock(mtx);
    ++size_;
    tail->next = n;
    n->prev = tail;
    tail = n;
    head = head != nullptr ? head : tail;
  }

  // TODO(anirudh): By the time I extract this value my head might have changed.
  // There isn't any point of this API ?
  T front() {
    std::scoped_lock lock(mtx);
    return head->value;
  }

  T pop_front() {
    std::scoped_lock lock(mtx);
    --size_;
    assert(head != nullptr);
    auto x = head->value;
    head = head->next;
    tail = head == nullptr ? nullptr : tail;
  }

  T& emplace(iterator hint, T&& value) {
    // TODO(anirudh): How do I update
    auto* n = new Node(std::forward<T>(value));
    std::scoped_lock(hint->mtx);
    std::optional<std::scoped_lock<std::mutex>> lock_on_next;
    if (hint->next) {
      lock_on_next.emplace(hint->next->mtx);
    }
    n->next = hint->next;
    n->prev = hint;
    hint->next = n;
    n->next->prev = n;
  }

  void erase(iterator itr){kk

  }

  std::mutex mtx;
  Node* head;
  Node* tail;
  // TODO(anirudh): How do I maintain this ? Make this an atomic ?
  size_t size_ = 0;
};

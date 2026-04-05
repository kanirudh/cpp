//
// Created by Anirudh Agrawal on 4/5/26.
//

#ifndef CPP_CRTP_NEW_H
#define CPP_CRTP_NEW_H

#include <atomic>
#include <thread>
#include <variant>
#include <vector>

class AlgoI {
public:
  template <typename Self>
  void Poll(this Self&& self) {
    self.PollImpl();
  }

  void PollImpl() {}
};

// AlgoVariant must be a std::variant of concrete algo types.
// std::visit dispatches statically to each type's Poll — no virtual calls.
template <typename AlgoVariant>
class WorkerThread {
public:
  template <typename Algo>
  void AddAlgo(Algo&& algo) {
    algos_.emplace_back(std::forward<Algo>(algo));
  }

  void Start() {
    running_.store(true, std::memory_order_relaxed);
    thread_ = std::thread([this] { Run(); });
  }

  void Stop() {
    running_.store(false, std::memory_order_relaxed);
    if (thread_.joinable()) thread_.join();
  }

  ~WorkerThread() { Stop(); }

private:
  void Run() {
    while (running_.load(std::memory_order_relaxed)) {
      for (auto& algo : algos_) {
        std::visit([](auto& a) { a.Poll(); }, algo);
      }
    }
  }

  std::vector<AlgoVariant> algos_;
  std::thread thread_;
  std::atomic<bool> running_{false};
};

#endif  // CPP_CRTP_NEW_H

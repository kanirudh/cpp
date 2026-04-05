//
// Created by Anirudh Agrawal on 4/5/26.
//

#include "design_patterns/crtp_new.h"
#include <iostream>
#include <chrono>
#include "gtest/gtest.h"

class LoggingAlgo : public AlgoI {

public:
  void PollImpl() {
    std::cout << i++ << std::endl;
  }

private:
  int i = 0;
};

class DoubleCountingAlgo : public AlgoI {
public:
  void PollImpl() {
    std::cout << (++i)++ << std::endl;
  }
private:
  int i = 0;
};

TEST(CrtpNew, basic) {
  WorkerThread<std::variant<LoggingAlgo, DoubleCountingAlgo>> worker;
  worker.AddAlgo(LoggingAlgo());
  worker.AddAlgo(DoubleCountingAlgo());
  worker.Start();
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  worker.Stop();
}

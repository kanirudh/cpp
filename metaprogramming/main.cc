// TODO(anirudh): This should be moved to a testing framework. Setup GoogleTest.
#include "conditional.h"

#include <iostream>
#include <array>

struct Stats {
	int total;
	int ongoing;
	int waiting;
	std::array<int, 10> timestamps;
};

template <bool EnableStats>
struct  Executor {
	void Process() {
		stats_.value().ongoing++;
	}
	int a;
	Conditional<Stats, EnableStats> stats_;
};
static_assert(sizeof(Executor<true>) == 56);
// NOTE: There is an additional 4 byte because the compiler is forced by the ABI to assign unique addresses to each member variable and also to generate the required padding.
static_assert(sizeof(Executor<false>) == 8);

void ConditionalTests() {
	Executor<true> executor_with_stats;
	std::cout << executor_with_stats.stats_.value().total << std::endl;
}

int main() {
  ConditionalTests();
  return 0;
}

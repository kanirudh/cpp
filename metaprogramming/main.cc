// TODO(anirudh): This should be moved to a testing framework. Setup GoogleTest.
#include "conditional.h"

#include <iostream>
#include <array>

struct Stats {
	int total = 0;
	int ongoing = 0;
	int waiting = 0;
	std::array<int, 10> timestamps;
};

template <bool EnableStats>
struct  Executor {
	void Process() {
		stats_.value().ongoing++;
	}
	int a;
	// NOTE: We are disabling empty base class optimization with no_unique_address.
	[[no_unique_address]] Conditional<Stats, EnableStats> stats_;
};
static_assert(sizeof(Executor<true>) == 56);
static_assert(sizeof(Executor<false>) == 4);

void ConditionalTests() {
	Executor<true> executor_with_stats;
	std::cout << executor_with_stats.stats_.value().total << std::endl;
}

int main() {
  ConditionalTests();
  return 0;
}

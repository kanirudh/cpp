/*
* Implements a rate_limiter which implments a list of callable and can be used in concurrent situation
*/


// TODO(anirudh): Define Callable which should have a operator()(void)
#include <type_traits>

struct TokenBucket {

};

struct LeakyBucket {

};

template <Callable callable, typename Strategy = TokenBucket>
class RateLimiter {
public:
	void Execute(Callable&& callable);

private:
	// TODO(anirudh): TBD

};

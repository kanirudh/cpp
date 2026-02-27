//
// Created by agrwl on 19-07-2025.
//

#include "TokenBucketRateLimiter.h"

TokenBucketRateLimiter::TokenBucketRateLimiter(int capacity, int rate_per_sec) : capacity_(capacity), rate_per_sec_(rate_per_sec) {
}
bool TokenBucketRateLimiter::Acquire() { return false; }
void TokenBucketRateLimiter::Refill() {}
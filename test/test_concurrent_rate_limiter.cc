//
// Created by agrwl on 19-07-2025.
//

#include "../concurrency/TokenBucketRateLimiter.h"
#include "concurrency/TokenBucketRateLimiter.h"
#include "gtest/gtest.h"

TEST(TokenBucketRateLimiter, construction) {
  auto limiter = TokenBucketRateLimiter(10, 10);

}
